CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g
LDFLAGS = -lsox -lfftw3 -lm

all: test

fourrier.o:

test.o: fourrier.h

test: fourrier.o test.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) fourrier.o test.o
	$(RM) test
