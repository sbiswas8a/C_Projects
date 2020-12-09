CC = gcc
CFLAGS = -Wall -std=c99 -g

select: select.o match.o text.o

select.o: select.c match.h text.h

match.o: match.c match.h text.h

text.o: text.c text.h

clean:
	rm -f select.o match.o text.o
	rm -f select
	rm -f output.txt
