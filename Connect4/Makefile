CC = gcc
CFLAGS = -Wall -std=c99 -g

connect4: connect4.o board.o check.o

connect4.o: connect4.c board.h check.h

board.o: board.c board.h

check.o: check.c check.h

clean:
	rm -f connect4.o board.o check.o
	rm -f connect4
	rm -f output.txt
