 /***************************************************************************
 *  FILE: pmms.h
 *  AUTHOR: Connor Beardsmore - 15504319
 *  UNIT: OS200 Assignment S1 - 2016
 *  PURPOSE: Header file for pmms.c
 *  LAST MOD: 07/05/16
 *  REQUIRES: stdio.h, stdlib.h, unistd.h, fcntl.h, semaphore.h, mman.h
 *            stat.h, wait.h, fileIO.h
 ***************************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "fileIO.h"

//---------------------------------------------------------------------------
// CONSTANTS

#define SUBTOTAL_EMPTY 0

//---------------------------------------------------------------------------
// STRUCT: Stores the value of subtotal and the ID of the child that
//         created it. Also stores row number that the child calculated.

typedef struct
{
    int value;
    int rowNum;
    int childPID;
} Subtotal;

//---------------------------------------------------------------------------
// STRUCT: Stores 3 locks for use in producer-consumer problem.
//         Mutex provides mutual exclusion to data.
//         Full and empty are semaphores to signal actions
//         from the producer and consumer.

typedef struct
{
    sem_t mutex;
    sem_t full;
    sem_t empty;
} Synchron;

//---------------------------------------------------------------------------
// FUNCTION PROTOTYPES

void producer(Synchron*, Subtotal*, int*, int*, int*, int, int);
void consumer(Synchron*, Subtotal*, int*, int);
int createLocks(Synchron*);
int destroyLocks(Synchron*);

//---------------------------------------------------------------------------
