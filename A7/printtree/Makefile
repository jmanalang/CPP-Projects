# Makefile for the print tree assignment

OBJS = term_control.o error_handling.o print.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic -ansi $(DEBUG)
LFLAGS = -Wall $(DEBUG)

programs: main

main: $(OBJS)
	$(CC) $(LFAGS) $(OBJS) -o main

main.o: main.cpp BTree.h term_control.h error_handling.h
	$(CC) -c $(CFLAGS) main.cpp

# this is where your code goes
print.o: print.cpp BTree.h term_control.o
	$(CC) -c $(CFLAGS) print.cpp

# error handling routines make use of terminal control routines
error_handling.o : term_control.o error_handling.h error_handling.cpp
	$(CC) -c $(CFLAGS) error_handling.cpp

# this object file is at the "lowest level"
term_control.o : term_control.h term_control.cpp
	$(CC) -c $(CFLAGS) term_control.cpp

clean:
	rm -f *.o a.out main
