 /***************************************************************************
 *	FILE: multiProcess.java												   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: OS200 Assignment S1 - 2016 														   
 *	PURPOSE: 
 *	LAST MOD: 16/04/16	
 *  REQUIRES: stdio.h, stdlib.h, multiProcess.h				   
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
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

	// RENAME ARG'S FOR BETTER CODE READABILITY
	char* matrixAFile = argv[1];
	char* matrixBFile = argv[2];
	int firstRows = atoi( argv[3] );
	int firstCols = atoi( argv[4] );
	int secondRows = atoi( argv[4] );
	int secondCols = atoi( argv[5] );
	int productRows = atoi( argv[3] );
	int productCols = atoi( argv[5] );					

	// VALIDATE THAT M,N,K ARE ALL 1 OR MORE
	if ( ( firstRows < 1 ) || ( firstCols < 1 ) || ( secondCols < 1 ) )
	{
		printf("ERROR: Matrix dimensions must be POSITIVE value.\n");
		return 2;
	}	

	// INITIALISE THREE MATRIX STRUCT
	Matrix* first = makeMatrix( firstRows, firstCols );
	Matrix* second = makeMatrix( secondRows, secondCols );
	Matrix* product = makeMatrix( productRows, productCols );	

	// INITIALISE SUBTOTAL
	Subtotal* subtotal = (Subtotal*)malloc( sizeof(Subtotal) );
	subtotal->value = 0;
	subtotal->childPID = 0;

	// READ MATRIX first/second ELEMENTS FROM FILE
	readFile( matrixAFile, first );
	readFile( matrixBFile, second);

	// PRINT CONTENTS OF ALL 3 MATRICES
	printMatrix(first);
	printMatrix(second);
	printMatrix(product);

	// FREE ALL MALLOC'D MEMORY TO AVOID MEMORY LEAKS
	freeMatrix(first);
	freeMatrix(second);
	freeMatrix(product);

	return 0;
}

//--------------------------------------------------------------------------
// FUNCTION: outputTotals()
// IMPORT: total (int)
// PURPOSE: Output process and subtotals and final total to standard out.

void outputTotals(int total)
{
	printf("Total: %d", total);
}

//--------------------------------------------------------------------------
