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


	size_t firstSize = sizeof(int) * ( (atoi(argv[3]) ) * ( atoi(argv[4]) ) );

	int firstFD = shm_open( "first", O_CREAT | O_RDWR, 0666 );
	int firstElementsFD = shm_open( "first_elements", O_CREAT | O_RDWR, 0666 );

	ftruncate( firstFD, sizeof(Matrix) );
	ftruncate( firstElementsFD, firstSize );

	Matrix* first = (Matrix*)mmap( 0, sizeof(Matrix), PROT_WRITE, MAP_SHARED, firstFD, 0 );

	first->rows = atoi(argv[3]);
	first->cols = atoi(argv[4]);
	first->elements = (int*)mmap( 0, firstSize, PROT_WRITE, MAP_SHARED, firstElementsFD, 0 );

	readFile( argv[1], first );

	printMatrix(first);

			
	return 0;
}

//--------------------------------------------------------------------------
// FUNCTION: outputTotals()
// IMPORT: total (int)
// PURPOSE: Output process and subtotals and final total to standard out.

void outputTotals(int total, Subtotal* subtotal)
{
	printf("Subotal: %d, Child PID: %d", subtotal->value, subtotal->childPID);
	printf("Total: %d", total);
}

//--------------------------------------------------------------------------
