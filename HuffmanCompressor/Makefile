CC = gcc
CFLAGS = -O2 -Wall -std=c99 -g

all: deflate inflate

deflate: deflate.o bitbuffer.o codes.o

deflate.o: deflate.c bitbuffer.h

inflate: inflate.o bitbuffer.o codes.o -lm

inflate.o: inflate.c bitbuffer.h

bitbuffer.o: bitbuffer.c bitbuffer.h

codes.o: codes.c codes.h

clean:
	rm -f codes.o bitbuffer.o inflate.o deflate.o
	rm -f inflate deflate
