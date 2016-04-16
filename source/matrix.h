 /***************************************************************************
 *	FILE: matrix.h							   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: UCP Assignment. S2 - 2015													   
 *	PURPOSE: Header file for matrix.h
 *	LAST MOD: 16/04/16	
 *  REQUIRES: NONE			   
 ***************************************************************************/

// STRUCT DECLARATIONS

typedef struct 
{
	int cols;
	int rows;
	int** matrix;
} Matrix;

//--------------------------------------------------------------------------
// FUNCTION PROTOTYPES

Matrix* makeMatrix(int, int);
void freeMatrix(Matrix*);
void printMatrix(Matrix*);

//--------------------------------------------------------------------------
 