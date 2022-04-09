# Makefile

CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lfftw3 -lm -lsox

all: test 

test : test.o write.o read.o
write.o : write.c write.h
read.o : read.c read.h

.PHONY: clean

clean:
	${RM} test
	${RM} test.o
	${RM} read.o
	${RM} write.o

# END
