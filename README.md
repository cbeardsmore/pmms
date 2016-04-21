######Connor Beardsmore - 15504319
######Semester 1, 2016

##OS200 Assignment  

#####Purpose

Implementation of matrix multiplication in C, utilizing multiple processes. Shared memory is established via POSIX's shm_open(), and synchronization is ensured via POSIX semaphores.
 
#####File List

	.c FILES
	--------
	multiProcess.c
	matrix.c
	fileIO.c

	.h FILES
	--------
	multiProcess.h
	matrix.h
	fileIO.h

	OTHER
	-----
	Makefile
	README.md
	

#####Instructions to Run

*For Multiprocess:*

	./multiProcess [file A] [file B] [M] [N] [K]

*For Multithreads:*  

	./multiThread [file A] [file B] [M] [N] [K]
	
*where:*  
  
- file A = Matrix A Filename
- file B = Matrix B Filename
- M = Matrix A Rows
- N = Matrix A Columns / Matrix B Rows
- K = Matrix B Columns	

#####References