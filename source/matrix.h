 /***************************************************************************
 *	FILE: matrix.h							   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: UCP Assignment. S2 - 2015													   
 *	PURPOSE: Header file for matrix.h
 *	LAST MOD: 16/04/16	
 *  REQUIRES: NONE			   
 ***************************************************************************/

#pragma once

//--------------------------------------------------------------------------

typedef struct 
{
	int rows;
	int cols;
	int* elements;
} Matrix;

//--------------------------------------------------------------------------

typedef struct 
{
	Matrix first;
	Matrix second;
	Matrix third;
} Matrices;

//--------------------------------------------------------------------------

void printMatrix(Matrix*);

//--------------------------------------------------------------------------