######Connor Beardsmore - 15504319
######Semester 1, 2016

##OS200 Assignment  

#####Purpose

Implementation of a matrix multiplication calculator in C. The data from the two matrices to mutiply are read from file. The calculator outputs the subtotal of every row, plus the grand total of all the rows. Part A utilizes Multiprocessing and Part B utilizes Multithreading.
Shared memory is established via POSIX's shm_open(). Synchronization is ensured via the use of POSIX semaphores, mutexes and conditions.
 
#####File List

	.c FILES
	--------
	multiProcess.c
	multiThread.c
	matrix.c
	fileIO.c

	.h FILES
	--------
	multiProcess.h
	multiThread.c
	matrix.h
	fileIO.h

	OTHER
	-----
	Makefile
	README.md
	/testFiles
	

#####Instructions to Compile + Run

*To Compile, choose one of the following:*

	make all
	make multiProcess
	make multiThread

*To Run Multiprocess:*

	./multiProcess [file A] [file B] [M] [N] [K]

*To Run Multithreads:*  

	./multiThread [file A] [file B] [M] [N] [K]
	
*where:*  
  
- file A = Matrix A Filename
- file B = Matrix B Filename
- M = Matrix A Rows
- N = Matrix A Columns / Matrix B Rows
- K = Matrix B Columns	

#####References

Silberschatz, Abraham, Peter B. Galvin, and Greg Gagne. *Operating System Concepts*. 9th ed. Reading, MA: Addison-Wesley, 1994.