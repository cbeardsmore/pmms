 /***************************************************************************
 *	FILE: pmms.c											   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: OS200 Assignment S1 - 2016 														   
 *	PURPOSE: Matrix multiplication using multiprocessing and shared memory
 *	LAST MOD: 26/04/16	
 *  REQUIRES: pmms.h				   
 ***************************************************************************/

#include "pmms.h" 

//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	// ENSURE ONLY 6 COMMAND LINE ARGUMENTS ENTERED
	if ( argc != 6 )
	{
		printf( "Usage: ./multiProcess [Matrix A File] [Matrix B File] [M] [N] [K]\n" );
		printf( "Please see README for detailed steps on how to run!\n" );
		return 1;
	}	

	// VALIDATE THAT M,N,K ARE ALL 1 OR MORE
	if ( ( atoi(argv[3]) < 1 ) || ( atoi(argv[4]) < 1 ) ||  ( atoi(argv[5]) < 1 ) )
	{
		printf("ERROR: Matrix dimensions must be POSITIVE value.\n");
		return 2;
	}	

	// RENAME COMMAND LINE ARGUMENTS FOR CODE READABILITY
	char* fileA = argv[1];
	char* fileB = argv[2];
	int M = atoi( argv[3] );
	int N = atoi( argv[4] );
	int K = atoi( argv[5] );

	// VARIABLE DECLARATIONS
	int total = 0;
	int *first, *second, *product;
	int firstFD, secondFD, productFD, subtotalFD, locksFD;
	Subtotal* subtotal;
	Synchron* locks;

	// CALCULATE TOTAL SIZE NEEDED FOR DATA OF THE 3 MATRICES
	size_t firstSize = sizeof(int) *  M * N ;
	size_t secondSize = sizeof(int) * N * K;
	size_t productSize = sizeof(int) * M * K;

	// CREATE SHARED MEMORY SEGMENTS FOR 3 MATRICES, SUBTOTAL AND LOCKS
	firstFD = shm_open( "matrixA", O_CREAT | O_RDWR, 0666 ); 
	secondFD = shm_open( "matrixB", O_CREAT | O_RDWR, 0666 ); 
	productFD = shm_open( "matriXC", O_CREAT | O_RDWR, 0666 ); 
	subtotalFD = shm_open( "subtotal", O_CREAT | O_RDWR, 0666 );
	locksFD = shm_open( "synchronization", O_CREAT | O_RDWR, 0666 );

	// TRUNCATE SEGMENTS TO APPRIORIATE SIZES
	ftruncate( firstFD, firstSize );
	ftruncate( secondFD, secondSize );
	ftruncate( productFD, productSize );
	ftruncate( subtotalFD, sizeof(Subtotal) );
	ftruncate( locksFD, sizeof(Synchron) );

	// MAP SHARED MEMORY SEGMENTS TO ADDRESS SPACE, ASSIGN TO POINTERS
	first = (int*)mmap( 0, firstSize, PROT_READ | PROT_WRITE, MAP_SHARED, firstFD, 0 );
	second = (int*)mmap( 0, secondSize, PROT_READ | PROT_WRITE, MAP_SHARED, secondFD, 0 );
	product = (int*)mmap( 0, productSize, PROT_READ | PROT_WRITE, MAP_SHARED, productFD, 0 );
	subtotal = (Subtotal*)mmap( 0, sizeof(Subtotal), PROT_READ | PROT_WRITE, MAP_SHARED, subtotalFD, 0 );
	locks = (Synchron*)mmap( 0, sizeof(Synchron), PROT_READ | PROT_WRITE, MAP_SHARED, locksFD, 0 );

	// READ DATA FROM FILE INTO MATRIX SHARED MEMORY
	readFile( fileA, first, M, N );
	readFile( fileB, second, N, K );

	// INITIAL SUBTOTAL FIELDS TO "EMPTY"
	subtotal->value = SUBTOTAL_EMPTY;
	subtotal->childPID = SUBTOTAL_EMPTY;
	subtotal->rowNumber = SUBTOTAL_EMPTY;

	// INITIALISE THE SEMAPHORES
	createLocks(locks);

	// CREATE 10 CHILDREN PROCESSES
	// DOUBLE FORKING AVOIDS ZOMBIE PROCESSES
	int pid = -1;
	int parent_pid = getpid();
	int status;
	
 	for ( int ii = 0; ii < M; ii++ )
 	{
		if ( pid != 0 )
		{
		if ( parent_pid == getpid() )	//only parent forks
		{	
 			pid = fork();
		}	
			if ( pid == 0 )		//child
			{
				if ( 0 == fork() ) //grandchild
				{
					sleep(1);	//let child die
				}	
				else 			// if your not grandchild, and pid==0, you must be child. die
				{
					exit(0);
				}
			}
			else 		//parent calls wait
			{
				waitpid(pid, &status, 0);
			}	
		}
 	}	


	// CONSUMER. PARENT WAITS FOR SUBTOTAL TO NOT BE EMPTY.
	if ( pid != 0 )
	{	
		consumer(locks, subtotal, &total, M);
	}	

	// PRODUCER. CHILD STORES CALCULATION IN SUBTOTAL.
	if ( pid == 0 )
	{		
		producer(locks, subtotal, first, second, product, N, K);
		// CHILD EXITS IMMEDIATELY AFTER IT DOES CACLULATIONS
		_exit(0);
	}	

	// PARENT DESTORYS ALL SEMAPHORES
	destroyLocks(locks);

	// PRINT CONTENT OF ALL 3 MATRICES
	//printMatrices( first, second, product );

	// OUTPUT FINAL TOTAL
	printf("\nFINAL TOTAL: %d\n", total);

	return 0;
}
//---------------------------------------------------------------------------
// FUNCTION: producer
// IMPORT: locks (Synchron*), subtotal (Subtotal*), first (Matrix*), second (Matrix*), product (Matrix*)
// PURPOSE: Parent process consumes the subtotal + childPID create by children.

void producer( Synchron* locks, Subtotal* subtotal, int* first, int* second, int* product, int N, int K)
{
	int value, rowNumber, offsetA, offsetC;
	int total = 0;

	sem_wait(&locks->mutex);

		rowNumber = subtotal->rowNumber;
		subtotal->rowNumber += 1;

	sem_post(&locks->mutex);

	offsetA = rowNumber * N;
	offsetC = rowNumber * K;


	for ( int ii = 0; ii < K; ii++ )
	{		
		value = 0;

		for ( int jj = 0; jj < N; jj++ )
		{			
			value += first[offsetA + jj] * second[jj * K + ii];		
		}	
		
		product[offsetC + ii] = value;
	}	

	for ( int kk = 0; kk < K; kk++ )
	{
		total += product[offsetC + kk];
	}

	sem_wait(&locks->empty);		
		sem_wait(&locks->mutex);

			subtotal->childPID = getpid();
			subtotal->value = total;

		sem_post(&locks->mutex);
	sem_post(&locks->full);

}

//---------------------------------------------------------------------------
// FUNCTION: consumer
// IMPORT: locks (Synchron*), subtotal (Subtotal*), total (int*), productRows (int)
// PURPOSE: Parent process consumes the subtotal + childPID create by children.

void consumer(Synchron* locks, Subtotal* subtotal, int* total, int productRows)
{
	for ( int ii = 0; ii < productRows; ii++ )
	{
		sem_wait(&locks->full);
			sem_wait(&locks->mutex);
		
			printf( "subtotal: %d, childPID: %d\n", subtotal->value, subtotal->childPID );
			*total += subtotal->value;
			subtotal->value = 0;
			subtotal->childPID = 0;

			sem_post(&locks->mutex);
		sem_post(&locks->empty);				
	}
}

//---------------------------------------------------------------------------
// FUNCTION: createLocks
// IMPORT: locks (Synchron*)
// PURPOSE: Create the 3 POSIX semaphores required for locks.

void createLocks(Synchron* locks)
{
	sem_init( &locks->mutex, -1, 1 );
	sem_init( &locks->full, -1, 0 );
	sem_init( &locks->empty, -1, 1 );
}

//---------------------------------------------------------------------------
// FUNCTION: destroyLocks
// IMPORT: locks (Synchron*)
// PURPOSE: Destroy the 3 POSIX semaphores created for locks.

void destroyLocks(Synchron* locks)
{
	sem_destroy( &locks->mutex );
	sem_destroy( &locks->full );
	sem_destroy( &locks->empty );	
}

//---------------------------------------------------------------------------
