 /***************************************************************************
 *	FILE: multiProcess.java												   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: OS200 Assignment S1 - 2016 														   
 *	PURPOSE: 
 *	LAST MOD: 16/04/16	
 *  REQUIRES: multiProcess.h				   
 ***************************************************************************/

#include "multiProcess.h" 
#define MAX_FILE_LENGTH 40
#define SUBTOTAL_EMPTY 0

//--------------------------------------------------------------------------

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
	int firstRows = atoi( argv[3] );
	int firstCols = atoi( argv[4] );
	int secondRows = atoi( argv[4] );
	int secondCols = atoi( argv[5] );
	int productRows = atoi( argv[3] );
	int productCols = atoi( argv[5] );
	int total = 0;

	// CALCULATE TOTAL SIZE NEEDED FOR DATA OF THE 3 MATRICES
	// THIS IS THE SIZE REQUIRED TO STORE THE DATA IN "ELEMENTS"
	size_t firstSize = sizeof(int) * ( firstRows * firstCols );
	size_t secondSize = sizeof(int) * ( secondRows * secondCols );
	size_t productSize = sizeof(int) * ( productRows * productCols );
	size_t totalDataSize = firstSize + secondSize + productSize;	

	// CREATE SHARED MEMORY SEGMENTS FOR THE MATRICES AND THEIR DATA ELEMENTS
	int matricesFD = shm_open( "matrices", O_CREAT | O_RDWR, 0666 ); 
	int matricesDataFD = shm_open( "matrices_data", O_CREAT | O_RDWR, 0666 ); 

	// TRUNCATE SEGMENTS TO APPRIORIATE SIZES
	ftruncate( matricesFD, (3 * sizeof(Matrix)) );
	ftruncate( matricesDataFD, totalDataSize );

	// MAP MATRICES STRUCT TO ADDRESS SPACE, ASSIGN TO POINTERS
	Matrix* first = (Matrix*)mmap( 0, (3 * sizeof(Matrix)), PROT_WRITE, MAP_SHARED, matricesFD, 0 );
	Matrix* second = first + sizeof(Matrix);
	Matrix* product = second + sizeof(Matrix);

	// INITIALISE VARIABLES WITHIN THE MATRICES THEMSELVES
	// MAP THE ELEMENTS ARRAY IN THE MATRICES TO ADDRESS SPACE
	first->rows = firstRows;
	first->cols = firstCols;
	first->elements = (int*)mmap( 0, totalDataSize, PROT_WRITE, MAP_SHARED, matricesDataFD, 0 );
	second->rows = secondRows;
	second->cols = secondCols;
	second->elements = first->elements + firstSize;
	product->rows = productRows;
	product->cols = productCols;
	product->elements = second->elements + secondSize;

	// READ DATA FROM FILE INTO MATRIX ELEMENTS SHARED MEMORY
	readFile( fileA, first );
	readFile( fileB, second );

	// SET UP SHARED MEMORY FOR SUBTOTAL
	int subtotalFD = shm_open( "subtotal", O_CREAT | O_RDWR, 0666 );
	ftruncate( subtotalFD, sizeof(Subtotal) );
	Subtotal* subtotal = (Subtotal*)mmap( 0, sizeof(Subtotal), PROT_WRITE, MAP_SHARED, subtotalFD, 0 );

	// INITIAL SUBTOTAL FIELDS TO "EMPTY"
	subtotal->value = SUBTOTAL_EMPTY;
	subtotal->childPID = SUBTOTAL_EMPTY;

	// SET UP THE SEMAPHORE SHARED MEMORY
	int locksFD = shm_open( "synchronization", O_CREAT | O_RDWR, 0666 );
	ftruncate( locksFD, sizeof(Synchron) );
	Synchron* locks = (Synchron*)mmap( 0, sizeof(Synchron), PROT_WRITE, MAP_SHARED, locksFD, 0 );
	
	// INITIALISE THE SEMAPHORES
	createLocks(locks);
	locks->rowNumber = 0;

	// CREATE 10 CHILDREN PROCESSES
	int pid = -1;
	for ( int ii = 0; ii < productRows; ii++ )
	{
		if ( pid != 0 )
		{
			pid = fork();
		}	
	}	

	// CONSUMER. PARENT WAITS FOR SUBTOTAL TO NOT BE EMPTY
	if ( pid != 0 )
	{
		for ( int ii = 0; ii < productRows; ii++ )
		{
			consumer(locks, subtotal, &total);
		}	
	}	

	// PRODUCER. CHILD STORES CALCULATION IN SUBTOTAL
	if ( pid == 0 )
	{
		producer(locks, subtotal, first, second, product);
	}	


	if ( pid !=0 )
	{	
		// PARENT DESTORYS ALL SEMAPHORES
		destroyLocks(locks);

		// PRINT CONTENT OF ALL 3 MATRICES
		printMatrices( first, second, product );
		printf("total: %d\n", total);
	}

	return 0;
}
//--------------------------------------------------------------------------
// FUNCTION: producer
// IMPORT: locks (Synchron*), subtotal (Subtotal*), first (Matrix*), second (Matrix*), product (Matrix*)
// PURPOSE: Parent process consumes the subtotal + childPID create by children.

void producer( Synchron* locks, Subtotal* subtotal, Matrix* first, Matrix* second, Matrix* product)
{
		sem_wait(&locks->empty);
			sem_wait(&locks->mutex);
				



				subtotal->childPID = getpid();
				int value;
				int offsetC = locks->rowNumber * product->cols;
				int offsetA = locks->rowNumber * first->cols;

				for ( int ii = 0; ii < product->cols; ii++ )
				{
					value = 0;

					for ( int jj = 0; jj < first->cols; jj++ )
					{
						value += first->elements[offsetA + jj] * second->elements[jj * second->cols + ii];
					}	

					product->elements[offsetC + ii] = value;
				}	

				for ( int kk = 0; kk < product->cols; kk++ )
				{
					subtotal->value = subtotal->value + product->elements[offsetC + kk];
				}	


				locks->rowNumber = locks->rowNumber + 1;


			sem_post(&locks->mutex);
		sem_post(&locks->full);
}

//--------------------------------------------------------------------------
// FUNCTION: consumer
// IMPORT: locks (Synchron*), subtotal (Subtotal*), total (int*)
// PURPOSE: Parent process consumes the subtotal + childPID create by children.

void consumer(Synchron* locks, Subtotal* subtotal, int* total)
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

//--------------------------------------------------------------------------
// FUNCTION: createLocks
// IMPORT: locks (Synchron*)
// PURPOSE: Create the 3 POSIX semaphores required for locks.

void createLocks(Synchron* locks)
{
	sem_init( &locks->mutex, -1, 1 );
	sem_init( &locks->full, -1, 0 );
	sem_init( &locks->empty, -1, 1 );
}

//--------------------------------------------------------------------------
// FUNCTION: destroyLocks
// IMPORT: locks (Synchron*)
// PURPOSE: Destroy the 3 POSIX semaphores created for locks.

void destroyLocks(Synchron* locks)
{
	sem_destroy( &locks->mutex );
	sem_destroy( &locks->full );
	sem_destroy( &locks->empty );	
}

//--------------------------------------------------------------------------
