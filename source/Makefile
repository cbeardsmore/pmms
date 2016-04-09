#
# Makefile For Matrix Multiplication w. Multi-process and Multi-threading
# OS200 Assignment
# Last Modified: 09/04/16
# Connor Beardsmore - 15504319
#

# MAKE VARIABLES
EXEC = matrixMult
OBJ = matrixMult.o
CFLAGS = -Wall -ansi -pedantic -g
CC = gcc

# RULES + DEPENDENCIES
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

matrixMult.o : matrixMult.h
	$(CC) -c matrixMult.c $(CFLAGS)
				
clean:
	rm -f $(EXEC) $(OBJ)