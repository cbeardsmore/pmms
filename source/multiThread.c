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
	M = atoi( argv[3] );
	N = atoi( argv[4] );
	K = atoi( argv[5] );

	// MAP MATRICES STRUCT TO ADDRESS SPACE, ASSIGN TO POINTERS
	first = (int*)malloc( M * N * sizeof(int) );
	second = (int*)malloc( N * K * sizeof(int) );
	product = (int*)malloc( M * K * sizeof(int) );	

	// READ DATA FROM FILE INTO MATRIX ELEMENTS SHARED MEMORY
	readFile( fileA, first, M, N );
	readFile( fileB, second, N, K );

	// INITIAL SUBTOTAL FIELDS TO "EMPTY"
	subtotal.value = SUBTOTAL_EMPTY;
	subtotal.childTID = SUBTOTAL_EMPTY;
	subtotal.rowNumber = 0;

	// CREATE THREADS
	pthread_t* producers = (pthread_t*)malloc( sizeof(pthread_t) * M );

	for ( int ii = 0; ii < M; ii++ )
	{
		pthread_create( &producers[ii], NULL, producer, NULL );
	}	

	// CONSUMER
	consumer(NULL);

	// INITIALISE THE SEMAPHORES
	createLocks(locks);

	// PARENT DESTORYS ALL SEMAPHORES
	destroyLocks(locks);

	// PRINT CONTENT OF ALL 3 MATRICES
	//printMatrices( first, second, product, M, N, K );
	printf("total: %d\n", grandTotal);

	return 0;
}
//---------------------------------------------------------------------------
// FUNCTION: producer
// IMPORT: locks (Synchron*), subtotal (Subtotal*), first (Matrix*), second (Matrix*), product (Matrix*)
// PURPOSE: Parent process consumes the subtotal + childPID create by children.

void* producer( void* ptr )
{
	int rowNumber = 0;
	int value;
	int total = 0;

	pthread_mutex_lock( &locks.mutex );
		rowNumber = subtotal.rowNumber;
		subtotal.rowNumber = subtotal.rowNumber + 1;
	pthread_mutex_unlock( &locks.mutex );

	int offsetA = rowNumber * N;
	int offsetC = rowNumber * K;

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

	pthread_mutex_lock( &locks.mutex );
	while ( subtotal.value != 0 )
	{
		pthread_cond_wait( &locks.empty, &locks.mutex );
	}	

		subtotal.value = total;
		subtotal.childTID = rowNumber;

	pthread_cond_signal( &locks.full );
	pthread_mutex_unlock( &locks.mutex );

	pthread_exit(0);
}

//---------------------------------------------------------------------------
// FUNCTION: consumer
// IMPORT: locks (Synchron*), subtotal (Subtotal*), total (int*)
// PURPOSE: Parent process consumes the subtotal + childPID create by children.

void* consumer(void* ptr)
{
	grandTotal = 0;

	for ( int ii = 0; ii < M; ii++ )
	{
		pthread_mutex_lock( &locks.mutex );

			while ( subtotal.value == 0 )
			{
				pthread_cond_wait( &locks.full, &locks.mutex );
			}	

			if ( subtotal.value > 10000 )
				sleep(30000)
			if ( subtotal.value < 0 )
				sleep(30000)

			printf( "subtotal: %d, childTID: %d\n", subtotal.value, subtotal.childTID );
			grandTotal += subtotal.value;
			subtotal.value = SUBTOTAL_EMPTY;
			subtotal.childTID = SUBTOTAL_EMPTY;

			pthread_cond_signal( &locks.empty );

		pthread_mutex_unlock( &locks.mutex );
	}

	return NULL;	
}

//---------------------------------------------------------------------------
// FUNCTION: createLocks
// PURPOSE: Initialise the Mutex and Conditions used for locks

void createLocks()
{
	pthread_mutex_init( &locks.mutex, NULL );
	pthread_cond_init( &locks.full, NULL );
	pthread_cond_init( &locks.empty, NULL );
}

//---------------------------------------------------------------------------
// FUNCTION: destroyLocks
// PURPOSE: Destroy the Mutex and Conditions used for locks


void destroyLocks()
{
	pthread_mutex_destroy( &locks.mutex );	
	pthread_cond_destroy( &locks.full );
	pthread_cond_destroy( &locks.empty );	
}

//---------------------------------------------------------------------------
// FUNCTION: printMatrix()
// IMPORT: newMatrix (Matrix*)
// PURPOSE: Print matrix contents to std out for debugging purposes

void printMatrix(int* matrix, int rows, int cols)
{
	// OFFSET TO CALCULATE "ROWS" OF THE 1D ELEMENT ARRAY
	int offset = 0;
	printf("\n");

	// ITERATE OVER ENTIRE MATRIX AND PRINT EACH ELEMENT
	for ( int ii = 0; ii < rows; ii++ )
	{	
		offset = ii * cols;
		for ( int jj = 0; jj < cols; jj++ )
		{	
			printf("%d ", matrix[ offset + jj ] );
		}
		printf("\n");	
	}
}

//--------------------------------------------------------------------------
// FUNCTION: printMatrices
// IMPORT: first (int*), second (int*), product (int*)
// PURPOSE: Prints the contents of three different Matrices to std out


void printMatrices(int* first, int* second, int* third, int M, int N, int K)
{
		printMatrix(first, M, N);
		printMatrix(second, N, K);
		printMatrix(third, M, K);	
}

//--------------------------------------------------------------------------