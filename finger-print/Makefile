# Makefile

CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lfftw3 -lm -lsox

all: test 

test : test.o finger_print.o ../fourrier/fourrier.o
finger_print.o : finger_print.c finger_print.h ../fourrier/fourrier.o
../fourrier/fourrier.o : ../fourrier/fourrier.c ../fourrier/fourrier.h

.PHONY: clean

clean:
	${RM} test
	${RM} test.o
	${RM} test.d
	${RM} ../fourrier/fourrier.o
	${RM} ../fourrier/fourrier.d
	${RM} finger_print.o
	${RM} finger_print.d

# END
