 /***************************************************************************
 *	FILE: multiProcess.java												   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: OS200 Assignment S1 - 2016 														   
 *	PURPOSE: 
 *	LAST MOD: 09/04/15	
 *  REQUIRES: stdio.h, stdlib.h, multiProcess.h					   
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "multiProcess.h"

//--------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	// ENSURE ONLY 6 COMMAND LINE ARGUMENTS ENTERED
	if ( argc != 6 )
	{
		printf( "Usage: ./multiProcess [Matrix A File] [Matrix B File] [M] [N] [K]\n" );
		return 1;
	}	

	// RENAME ARG'S FOR BETTER CODE READABILITY
	char* matrixA = argv[1];
	char* matrixB = argv[2];
	int aRow = atoi( argv[3] ); 
	int aCol = atoi( argv[4] ); 
	int bRow = atoi( argv[4] );  
	int bCol = atoi( argv[5] ); 

	// TOTAL VARIABLES
	int total = 0;

	// INITIALISE MATRIX STRUCTS


	// READ DATA FROM FILE INTO MATRIXS



	// OUTPUT FINAL CALCULATIONS
	outputTotals(total);

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
