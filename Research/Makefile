# Makefile

CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lfftw3 -lm -lsox

all: test 

test : test.o research.o 
research.o : research.c research.h
read.o : ../read/read.c ../read/read.h

.PHONY: clean

clean:
	${RM} test
	${RM} test.o
	${RM} test.d
	${RM} ../read/read.o
	${RM} ../read/read.d
	${RM} research.o
	${RM} research.d

# END
