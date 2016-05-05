 /***************************************************************************
 *	FILE: pmms.h
 *	AUTHOR: Connor Beardsmore - 15504319
 *	UNIT: OS200 Assignment S1 - 2016
 *	PURPOSE: Header file for pmms.c
 *	LAST MOD: 24/04/16
 *  REQUIRES: stdlib.h, pthread.h, fileIO.h
 ***************************************************************************/

#pragma once

#include <stdlib.h>
#include <pthread.h>
#include "fileIO.h"

//---------------------------------------------------------------------------
// CONSTANTS

#define SUBTOTAL_EMPTY 0

//---------------------------------------------------------------------------
// STRUCT: Stores the value of subtotal and the ID of the thread that
//		   created it. Also stores row number that the thread calculated.

typedef struct
{
	int value;
	int threadID;
	int rowNumber;
} Subtotal;

//---------------------------------------------------------------------------
// STRUCT: Stores 3 locks for use in producer-consumer problem. Mutex
//         provides mutual exclusion to data. Full and empty are conditions
//         that the producer and consumer wait until they are met.

typedef struct
{
	pthread_mutex_t mutex;
	pthread_cond_t full;
	pthread_cond_t empty;
} Synchron;

//---------------------------------------------------------------------------
// GLOBAL VARIABLES FOR USE IN MULTITHREADS

Subtotal subtotal;
int grandTotal;
int status;
Synchron locks;
int* first;
int* second;
int* product;
int M;
int N;
int K;

//---------------------------------------------------------------------------
// FUNCTION DECLARATIONS

void* producer(void* ptr);
void* consumer(void* ptr);
int destroyLocks();
int createLocks();
void freeMatrices(int*, int*, int*);
void printMatrix(int*, int, int);
void printMatrices(int*, int*, int*, int, int, int);

//---------------------------------------------------------------------------
