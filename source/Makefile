#
# Makefile For Matrix Multiplication w. Multi-process and Multi-threading
# OS200 Assignment
# Last Modified: 28/04/16
# Connor Beardsmore - 15504319
#

# MAKE VARIABLES
EXEC1 = pmms
OBJ1 = pmms.o fileIO.o
EXEC2 = tmms
OBJ2 = tmms.o fileIO.o

CFLAGS = -Wall -Wextra -std=c99 -lrt -pthread -D _XOPEN_SOURCE=500
CC = gcc

# RULES + DEPENDENCIES
all: $(EXEC1) $(EXEC2)

$(EXEC1) : $(OBJ1)
	$(CC) $(OBJ1) -o $(EXEC1) $(CFLAGS)

$(EXEC2) : $(OBJ2)
	$(CC) $(OBJ2) -o $(EXEC2) $(CFLAGS)

pmms.o : pmms.c pmms.h fileIO.h
	$(CC) -c pmms.c $(CFLAGS)

tmms.o : tmms.c tmms.h fileIO.h
	$(CC) -c tmms.c $(CFLAGS)

fileIO.o : fileIO.c fileIO.h
	$(CC) -c fileIO.c $(CFLAGS)

clean:
	rm -f $(EXEC1) $(OBJ1) $(EXEC2) $(OBJ2)
