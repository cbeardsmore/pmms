######Connor Beardsmore - 15504319
######Semester 1, 2016

##OS200 Assignment  

#####Purpose

Implementation of a matrix multiplication calculator in C. The data from the two matrices to mutiply are read from file. The calculator outputs the subtotal of every row, plus the grand total of all the rows. Part A *(pmms)* utilizes Multiprocessing and Part B *(tmms)* utilizes Multithreading.
Shared memory is established via POSIX's shm_open(). Synchronization is ensured via the use of POSIX semaphores, mutexes and conditions.
 
#####File List

	.c FILES
	--------
	pmms.c
	tmms.c
	fileIO.c

	.h FILES
	--------
	pmms.h
	tmms.c
	fileIO.h

	OTHER
	-----
	Makefile
	README.md
	/testFiles
	

#####Instructions to Compile + Run

*To Compile, choose one of the following:*

	make all
	make pmms
	make tmms

*To Run Multiprocess:*

	./pmms [file A] [file B] [M] [N] [K]

*To Run Multithreads:*  

	./tmms [file A] [file B] [M] [N] [K]
	
*where:*  
  
- file A = Matrix A Filename
- file B = Matrix B Filename
- M = Matrix A Rows
- N = Matrix A Columns / Matrix B Rows
- K = Matrix B Columns	

#####Matrix Multiplication

The product matrix $$C$$'s elements of muliplying matrix $$A$$ with matrix $$B$$ is as follows:

$$C_{i,j}=\sum_{r=1}^N A_{i,r}B_{r,j}$$

The image below illustrates an example of this calculation:

![Matrix Mult. Example](/Users/Connor/Google\ Drive/OS200/Assignment/documentation/mm_example.png)

#####References

Silberschatz, Abraham, Peter B. Galvin, and Greg Gagne. *Operating System Concepts*. 9th ed. Reading, MA: Addison-Wesley, 1994.