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
	int total = 420;

	// CALCULATE TOTAL SIZE NEEDED FOR 3 MATRICES
	size_t firstSize = sizeof(int) * ( firstRows * firstCols );
	size_t secondSize = sizeof(int) * ( secondRows * secondCols );
	size_t productSize = sizeof(int) * ( productRows * productCols );	

	// CREATE SHARED MEMORY SEGMENTS FOR ALL 3 MATRICES + ELEMENTS
	int firstFD = shm_open( "first", O_CREAT | O_RDWR, 0666 );
	int firstData = shm_open( "first_elements", O_CREAT | O_RDWR, 0666 );
	int secondFD = shm_open( "second", O_CREAT | O_RDWR, 0666 );
	int secondData = shm_open( "second_elements", O_CREAT | O_RDWR, 0666 );
	int productFD = shm_open( "product", O_CREAT | O_RDWR, 0666 );
	int productData = shm_open( "product_elements", O_CREAT | O_RDWR, 0666 );

	// TRUNCATE SEGMENTS TO APPRIORIATE SIZES
	ftruncate( firstFD, sizeof(Matrix) );
	ftruncate( firstData, firstSize );
	ftruncate( secondFD, sizeof(Matrix) );
	ftruncate( secondData, secondSize );
	ftruncate( productFD, sizeof(Matrix) );
	ftruncate( productData, productSize );

	// MAP MATRIX MEMORY TO ADDRESS SPACE
	Matrix* first = (Matrix*)mmap( 0, sizeof(Matrix), PROT_WRITE, MAP_SHARED, firstFD, 0 );
	Matrix* second = (Matrix*)mmap( 0, sizeof(Matrix), PROT_WRITE, MAP_SHARED, secondFD, 0 );
	Matrix* product = (Matrix*)mmap( 0, sizeof(Matrix), PROT_WRITE, MAP_SHARED, productFD, 0 );

	// INITIALISE VARIABLES WITHIN THE MATRICES THEMSELVES
	first->rows = firstRows;
	first->cols = firstCols;
	first->elements = (int*)mmap( 0, firstSize, PROT_WRITE, MAP_SHARED, firstData, 0 );
	second->rows = secondRows;
	second->cols = secondCols;
	second->elements = (int*)mmap( 0, secondSize, PROT_WRITE, MAP_SHARED, secondData, 0 );
	product->rows = productRows;
	product->cols = productCols;
	product->elements = (int*)mmap( 0, productSize, PROT_WRITE, MAP_SHARED, productData, 0 );

	// READ DATA FROM FILE INTO MATRIX ELEMENTS SHARED MEMORY
	readFile( fileA, first );
	readFile( fileB, second );

	// SET UP SHARED MEMORY FOR SUBTOTAL
	int subtotalFD = shm_open( "subtotal", O_CREAT | O_RDWR, 0666 );
	ftruncate( subtotalFD, sizeof(Subtotal) );
	Subtotal* subtotal = (Subtotal*)mmap( 0, sizeof(Subtotal), PROT_WRITE, MAP_SHARED, subtotalFD, 0 );


	// CREATE 10 CHILDREN PROCESSES
	int pid = -1;
	for ( int ii = 0; ii < 10; ii++ )
	{
		if ( pid != 0 )
		{
			pid = fork();
		}	
	}	







	if ( pid !=0 )
	{	
		printMatrix(first);
		printMatrix(second);
		outputTotals(total, subtotal);
	}

	return 0;
}

//--------------------------------------------------------------------------
// FUNCTION: outputTotals()
// IMPORT: total (int)
// PURPOSE: Output process and subtotals and final total to standard out.

void outputTotals(int total, Subtotal* subtotal)
{
	printf("\n");
	printf("Subotal: %d, Child PID: %d\n", subtotal->value, subtotal->childPID);
	printf("Total: %d\n", total);
	printf("\n");	
}

//--------------------------------------------------------------------------
