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
	${RM} test.d
	${RM} read.o
	${RM} read.d
	${RM} write.o
	${RM} write.d

# END
