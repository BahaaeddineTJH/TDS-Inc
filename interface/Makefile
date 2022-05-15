#Makefile

CC = gcc 

CPPFLAGS =  `pkg-config gtk+-3.0 --cflags` -MMD
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = 
LDLIBS = `pkg-config gtk+-3.0 --libs` -lfftw3 -lm -lsox -rdynamic


all: main

main : main.o ../finger-print/finger_print.o ../fourrier/fourrier.o ../bytes/read.o ../bytes/write.o ../Research/research.o ../local-server/client.o ../Research/dictionary.o
../local-server/client.o : ../local-server/client.c ../local-server/client.h ../Research/research.o ../finger-print/finger_print.o ../fourrier/fourrier.o ../bytes/read.o
../Research/dictionary.o : ../Research/dictionary.c ../Research/dictionary.h
../finger-print/finger_print.o : ../finger-print/finger_print.c ../finger-print/finger_print.h ../fourrier/fourrier.o
../fourrier/fourrier.o : ../fourrier/fourrier.c ../fourrier/fourrier.h
../research/research.o : ../Research/research.c ../Research/research.h ../bytes/write.o
../bytes/read.o : ../bytes/read.c ../bytes/read.h
../bytes/write.o : ../bytes/write.c ../bytes/write.h


.PHONY: clean

clean:
	${RM} main
	${RM} save
	${RM} main.d
	${RM} main.o
	${RM} ../fourrier/fourrier.o
	${RM} ../fourrier/fourrier.d
	${RM} ../finger-print/finger_print.o
	${RM} ../finger-print/finger_print.d
	${RM} ../bytes/read.o 
	${RM} ../bytes/read.d
	${RM} ../bytes/write.o
	${RM} ../bytes/write.d
	${RM} ../Research/research.o
	${RM} ../Research/research.d
	${RM} ../Research/dictionary.o
	${RM} ../Research/dictionary.d
	${RM} ../local-server/client.o
	${RM} ../local-server/client.d

# END
