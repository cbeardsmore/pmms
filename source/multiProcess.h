 /***************************************************************************
 *	FILE: multiProcess.h							   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: UCP Assignment. S2 - 2015													   
 *	PURPOSE: Header file for multiProcess.c
 *	LAST MOD: 16/04/16	
 *  REQUIRES: matrix.h, fileIO.h		   
 ***************************************************************************/

#include "matrix.h"
#include "fileIO.h"

//--------------------------------------------------------------------------

typedef struct 
{
	int value;
	int childPID;
} Subtotal;

//-------------------------------------------------------------------------- 

void outputTotals(int);

//--------------------------------------------------------------------------
 