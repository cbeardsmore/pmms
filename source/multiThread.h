 /***************************************************************************
 *	FILE: multiThread.h												   
 *	AUTHOR: Connor Beardsmore - 15504319								  
 *	UNIT: OS200 Assignment S1 - 2016 														   
 *	PURPOSE: Header file for multiThread.c
 *	LAST MOD: 24/04/16	
 *  REQUIRES: stdio.h, stdlib.h, shm.h, mman.h, string.h, fcntl.h, unistd.h
 *			  matrix.h, fileIO.h, semaphore.			   
 ***************************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#include "matrix.h"
#include "fileIO.h"

//---------------------------------------------------------------------------

typedef struct 
{
	int value;
	int childPID;
	int rowNumber;
} Subtotal;

//---------------------------------------------------------------------------

typedef struct 
{
	pthread_mutex_t mutex;
	pthread_cond_t full;
	pthread_cond_t empty;
} Synchron;

//---------------------------------------------------------------------------

void producer( Synchron*, Subtotal*, Matrix*, Matrix*, Matrix*);
void consumer(Synchron*, Subtotal*, int*, int);
void destroyLocks(Synchron*);
void createLocks(Synchron*);

//---------------------------------------------------------------------------