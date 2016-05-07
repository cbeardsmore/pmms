# Makefile For Matrix Multiplication w. Multi-processing
# OS200 Assignment
# Last Modified: 07/05/16
# Connor Beardsmore - 15504319

# MAKE VARIABLES
EXEC1 = pmms
OBJ1 = pmms.o fileIO.o
CFLAGS = -Wall -Wextra -std=c99 -lrt -pthread -D _XOPEN_SOURCE=500
CC = gcc


# RULES + DEPENDENCIES
$(EXEC1) : $(OBJ1)
	$(CC) $(OBJ1) -o $(EXEC1) $(CFLAGS)

pmms.o : pmms.c pmms.h fileIO.h
	$(CC) -c pmms.c $(CFLAGS)

fileIO.o : fileIO.c fileIO.h
	$(CC) -c fileIO.c $(CFLAGS)

clean:
	rm -f $(EXEC1) $(OBJ1)
