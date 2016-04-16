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
// FUNCTION: makeMatrix()
// IMPORT: rows (int), cols (int)
// EXPORT: newMatrix (Matrix*)
// PURPOSE: Allocate all memory needed for an int struct and initalize fields

Matrix* makeMatrix(int rows, int cols)
{
		Matrix* newMatrix = (Matrix*)malloc( sizeof(Matrix) );

		// SET ROWS AND COLUMN FIELDS
		newMatrix->rows = rows;
		newMatrix->cols = cols;

		// ALLOCATE MEMORY FOR ACTUAL ELEMENTS
		newMatrix->elements = (int**)calloc( rows, sizeof(int*) );
		for ( int ii = 0; ii < rows; ii++ )
			newMatrix->elements[ii] = (int*)calloc( cols, sizeof(int) );


		return newMatrix;
}
//--------------------------------------------------------------------------
// FUNCTION: freeMatrix()
// IMPORT: oldMatrix (Matrix*)
// PURPOSE: Free all memory associated with a matrix struct

void freeMatrix(Matrix* oldMatrix)
{
	// FREE EVERY INDIVIDUAL ROW OF THE MATRIX
	for ( int ii = 0; ii < oldMatrix->rows; ii++ )
			free( oldMatrix->elements[ii] );

	free( oldMatrix->elements );

	// FREE THE ACTUAL STRUCT
	free(oldMatrix);
}
//--------------------------------------------------------------------------
// FUNCTION: printMatrix()
// IMPORT: newMatrix (Matrix*)
// PURPOSE: Print matrix contents to std out for debugging purposes

void printMatrix(Matrix* newMatrix)
{
	printf("\n");

	// ITERATE OVER ENTIRE MATRIX AND PRINT EACH ELEMENT
	for ( int ii = 0; ii < newMatrix->rows; ii++ )
	{	
		for ( int jj = 0; jj < newMatrix->cols; jj++ )
		{	
			printf("%d ", newMatrix->elements[ii][jj] );
		}
		printf("\n");	
	}
}
//--------------------------------------------------------------------------