 /***************************************************************************
 *	FILE: multiThread.c										   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: OS200 Assignment S1 - 2016 														   
 *	PURPOSE: Matrix multiplication using multithreading and POSIX mutexs
 *	LAST MOD: 24/04/16	
 *  REQUIRES: multiThread.h				   
 ***************************************************************************/

#include "multiThread.h" 
#define MAX_FILE_LENGTH 40
#define SUBTOTAL_EMPTY 0

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
	int firstRows = atoi( argv[3] );
	int firstCols = atoi( argv[4] );
	int secondRows = atoi( argv[4] );
	int secondCols = atoi( argv[5] );
	int productRows = atoi( argv[3] );
	int productCols = atoi( argv[5] );

	// VARIABLE DECLARATIONS
	int total = 0;

	// CALCULATE TOTAL SIZE NEEDED FOR DATA OF THE 3 MATRICES
	// THIS IS THE SIZE REQUIRED TO STORE THE DATA IN "ELEMENTS"
	size_t firstSize = sizeof(Matrix) + sizeof(int) * ( firstRows * firstCols );
	size_t secondSize = sizeof(Matrix) + sizeof(int) * ( secondRows * secondCols );
	size_t productSize = sizeof(Matrix) + sizeof(int) * ( productRows * productCols );



	// MAP MATRICES STRUCT TO ADDRESS SPACE, ASSIGN TO POINTERS
	Matrix* first = (Matrix*)mmap( 0, firstSize, PROT_WRITE, MAP_SHARED, matrixAFD, 0 );
	Matrix* second = (Matrix*)mmap( 0, secondSize, PROT_WRITE, MAP_SHARED, matrixBFD, 0 );
	Matrix* product = (Matrix*)mmap( 0, productSize, PROT_WRITE, MAP_SHARED, matrixCFD, 0 );

	// INITIALISE VARIABLES WITHIN THE MATRICES THEMSELVES
	// MAP THE ELEMENTS ARRAY IN THE MATRICES TO ADDRESS SPACE
	first->rows = firstRows;
	first->cols = firstCols;
	first->elements = (int*)first + sizeof(Matrix);
	second->rows = secondRows;
	second->cols = secondCols;
	second->elements = (int*)second + sizeof(Matrix);
	product->rows = productRows;
	product->cols = productCols;
	product->elements = (int*)product + sizeof(Matrix);

	// READ DATA FROM FILE INTO MATRIX ELEMENTS SHARED MEMORY
	readFile( fileA, first );
	readFile( fileB, second );

	Synchron* locks;
	Subtotal* subtotal = (Subtotal*)malloc( sizeof(Subtotal) );

	// INITIAL SUBTOTAL FIELDS TO "EMPTY"
	subtotal->value = SUBTOTAL_EMPTY;
	subtotal->childPID = SUBTOTAL_EMPTY;
	subtotal->rowNumber = 0;



	// INITIALISE THE SEMAPHORES
	createLocks(locks);

	// CREATE 10 CHILDREN PROCESSES
	// DOUBLE FORKING AVOIDS ZOMBIE PROCESSES
	int pid = -1;
	int parent_pid = getpid();
	int status;
 	for ( int ii = 0; ii < productRows; ii++ )
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

	// CONSUMER. PARENT WAITS FOR SUBTOTAL TO NOT BE EMPTY
	if ( pid != 0 )
	{
		consumer(locks, subtotal, &total, productRows);
	}	

	// PRODUCER. CHILD STORES CALCULATION IN SUBTOTAL
	if ( pid == 0 )
	{
		producer(locks, subtotal, first, second, product);
		_exit(0);
	}	

	// PARENT DESTORYS ALL SEMAPHORES
	destroyLocks(locks);

	// PRINT CONTENT OF ALL 3 MATRICES
	printMatrices( first, second, product );
	printf("total: %d\n", total);

	return 0;
}
//---------------------------------------------------------------------------
// FUNCTION: producer
// IMPORT: locks (Synchron*), subtotal (Subtotal*), first (Matrix*), second (Matrix*), product (Matrix*)
// PURPOSE: Parent process consumes the subtotal + childPID create by children.

void producer( Synchron* locks, Subtotal* subtotal, Matrix* first, Matrix* second, Matrix* product)
{
						int value;
						int rowNumber;
						int total = 0;


	pthread_mutex_lock( &locks->mutex );
	while ( buffer != 0 )
	{
		pthread_cond_wait( &locks->empty, &locks->mutex );
	}	
	buffer = 1;
	pthread_cond_signal( &locks->full );
	pthread_mutex_unlock( &locks->mutex );






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
						total += product->elements[offsetC + kk];
					}

	pthread_exit(0);

}

//---------------------------------------------------------------------------
// FUNCTION: consumer
// IMPORT: locks (Synchron*), subtotal (Subtotal*), total (int*)
// PURPOSE: Parent process consumes the subtotal + childPID create by children.

void* consumer(void* ptr)
{
	for ( int ii = 0; ii < ITEMS; ii++ )
	{
		pthread_mutex_lock( &locks->mutex );
		while ( buffer == 0 )
		{
			pthread_cond_wait( &locks->full, &locks->mutex );
		}	
		buffer = 0;

				printf( "subtotal: %d, childPID: %d\n", subtotal->value, subtotal->childPID );
				*total += subtotal->value;
				subtotal->value = 0;
				subtotal->childPID = 0;

		pthread_cond_signal( &locks->empty );
		pthread_mutex_unlock( &locks->mutex );
	}	

	pthread_exit(0);
}

//---------------------------------------------------------------------------
// FUNCTION: createLocks
// IMPORT: locks (Synchron*)
// PURPOSE: Initialise the Mutex and Conditions used for locks

void createLocks(Synchron* locks)
{
	pthread_mutex_init( &locks->mutex, NULL );
	pthread_cond_init( &locks->full, NULL );
	pthread_cond_init( &locks->empty, NULL );
}

//---------------------------------------------------------------------------
// FUNCTION: destroyLocks
// IMPORT: locks (Synchron*)
// PURPOSE: Destroy the Mutex and Conditions used for locks


void destroyLocks(Synchron* locks)
{
	pthread_mutex_destroy();	
	pthread_cond_destroy( &locks->full );
	pthread_cond_destroy( &locks->empty );	
}

//---------------------------------------------------------------------------
