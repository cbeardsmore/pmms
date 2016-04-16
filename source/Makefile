#
# Makefile For Matrix Multiplication w. Multi-process and Multi-threading
# OS200 Assignment
# Last Modified: 16/04/16
# Connor Beardsmore - 15504319
#

# MAKE VARIABLES
EXEC1 = multiProcess
OBJ1 = multiProcess.o matrix.o
EXEC2 = multiThread
OBJ2 = multiThread.o

CFLAGS = -Wall -Wextra -Werror -std=c99 -g
CC = gcc

# RULES + DEPENDENCIES

$(EXEC1) : $(OBJ1)
	$(CC) $(OBJ1) -o $(EXEC1)	

multiProcess.o : multiProcess.c multiProcess.h matrix.h
	$(CC) -c multiProcess.c $(CFLAGS)

matrix.o : matrix.c matrix.h
	$(CC) -c matrix.c $(CFLAGS)	

clean:
	rm -f $(EXEC1) $(OBJ1) $(EXEC2) $(OBJ2)

# UNCOMMENT FOR WHEN PART A IS COMPLETE!	
#all:
#	$(EXEC1) $(EXEC2)
#multiThread.o : multiThread.c multiThread.h
#	$(CC) -c multiThread.c $(CFLAGS)
#$(EXEC2) : $(OBJ2)
#	$(CC) $(OBJ2) -o $(EXEC2)