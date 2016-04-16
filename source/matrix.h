 /***************************************************************************
 *	FILE: matrix.h							   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: UCP Assignment. S2 - 2015													   
 *	PURPOSE: Header file for matrix.h
 *	LAST MOD: 16/04/16	
 *  REQUIRES: NONE			   
 ***************************************************************************/

#ifndef MATRIX_H

 	#define MATRIX_H

//--------------------------------------------------------------------------

	typedef struct 
	{
		int cols;
		int rows;
		int** matrix;
	} Matrix;

//--------------------------------------------------------------------------

	Matrix* makeMatrix(int, int);
	void freeMatrix(Matrix*);
	void printMatrix(Matrix*);

//--------------------------------------------------------------------------
 
#endif
