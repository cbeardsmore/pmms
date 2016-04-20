 /***************************************************************************
 *	FILE: matrix.c							   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: UCP Assignment. S2 - 2015													   
 *	PURPOSE: Perform basic operations on the matrix struxt
 *	LAST MOD: 16/04/16	
 *  REQUIRES: stdio.h, stdlib.h, matrix.h		   
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h> 
#include "matrix.h"

//--------------------------------------------------------------------------
// FUNCTION: printMatrix()
// IMPORT: newMatrix (Matrix*)
// PURPOSE: Print matrix contents to std out for debugging purposes

void printMatrix(Matrix* newMatrix)
{
	// OFFSET TO CALCULATE "ROWS" OF THE 1D ELEMENT ARRAY
	int offset = 0;
	printf("\n");

	// ITERATE OVER ENTIRE MATRIX AND PRINT EACH ELEMENT
	for ( int ii = 0; ii < newMatrix->rows; ii++ )
	{	
		offset = ii * newMatrix->cols;
		for ( int jj = 0; jj < newMatrix->cols; jj++ )
		{	
			printf("%d ", newMatrix->elements[ offset + jj ] );
		}
		printf("\n");	
	}
}
//--------------------------------------------------------------------------