 /***************************************************************************
 *	FILE: multiProcess.h							   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: UCP Assignment. S2 - 2015													   
 *	PURPOSE: Header file for multiProcess.c
 *	LAST MOD: 17/10/15	
 *  REQUIRES: NONE			   
 ***************************************************************************/

// STRUCT DECLARATIONS

typedef struct 
{
	unsigned int columns;
	unsigned int rows;
	int** matrix;
} Matrix;

//--------------------------------------------------------------------------
// FUNCTION PROTOTYPES

void outputTotals(int);

 //--------------------------------------------------------------------------
 