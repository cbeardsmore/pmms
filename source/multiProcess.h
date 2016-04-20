 /***************************************************************************
 *	FILE: multiProcess.h							   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: UCP Assignment. S2 - 2015													   
 *	PURPOSE: Header file for multiProcess.c
 *	LAST MOD: 16/04/16	
 *  REQUIRES: stdio.h, stdlib.h, shm.h, mman.h, string.h, fcntl.h, unistd.h
 *			  matrix.h, fileIO.h		   
 ***************************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "matrix.h"
#include "fileIO.h"

//--------------------------------------------------------------------------

typedef struct 
{
	int value;
	int childPID;
} Subtotal;

//-------------------------------------------------------------------------- 

void outputTotals(int, Subtotal*);

//--------------------------------------------------------------------------
 