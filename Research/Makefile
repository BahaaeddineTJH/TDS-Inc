# Makefile

CC = gcc 

CPPFLAGS =  `pkg-config gtk+-3.0 --cflags` -MMD
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = 
LDLIBS = `pkg-config gtk+-3.0 --libs` -lfftw3 -lm -lsox -rdynamic

all: test 

test : test.o ../finger-print/finger_print.o ../fourrier/fourrier.o ../bytes/read.o ../bytes/write.o research.o dictionary.o 
../finger-print/finger_print.o : ../finger-print/finger_print.c ../finger-print/finger_print.h ../fourrier/fourrier.o
../fourrier/fourrier.o : ../fourrier/fourrier.c ../fourrier/fourrier.h
research.o : research.c research.h ../bytes/write.o dictionary.o
../bytes/read.o : ../bytes/read.c ../bytes/read.h
../bytes/write.o : ../bytes/write.c ../bytes/write.h
dictionary.o: dictionary.c dictionary.h

.PHONY: clean

clean:
	${RM} test
	${RM} test.d
	${RM} test.o
	${RM} ../local-server/client.o
	${RM} ../local-server/client.d
	${RM} ../fourrier/fourrier.o
	${RM} ../fourrier/fourrier.d
	${RM} ../finger-print/finger_print.o
	${RM} ../finger-print/finger_print.d
	${RM} ../bytes/read.o 
	${RM} ../bytes/read.d
	${RM} ../bytes/write.o
	${RM} ../bytes/write.d
	${RM} research.o
	${RM} research.d
	${RM} dictionary.o
	${RM} dictionary.d

# END
