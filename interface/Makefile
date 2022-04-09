#Makefile

CC = gcc -rdynamic

CPPFLAGS =  `pkg-config gtk+-3.0 --cflags` -MMD
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS =
LDLIBS = `pkg-config gtk+-3.0 --libs` -lfftw3 -lm -lsox


all: main save

main : main.o ../finger-print/finger_print.o ../fourrier/fourrier.o ../bytes/read.o ../bytes/write.o
save : save.o ../bytes/write.o
../finger-print/finger_print.o : ../finger-print/finger_print.c ../finger-print/finger_print.h ../fourrier/fourrier.o
../fourrier/fourrier.o : ../fourrier/fourrier.c ../fourrier/fourrier.h
../bytes/read.o : ../bytes/read.c ../bytes/read.h
../bytes/write.o : ../bytes/write.c ../bytes/write.h


.PHONY: clean

clean:
	${RM} main
	${RM} save
	${RM} main.d
	${RM} main.o
	${RM} save.o
	${RM} save.d
	${RM} ../fourrier/fourrier.o
	${RM} ../fourrier/fourrier.d
	${RM} ../finger-print/finger_print.o
	${RM} ../finger-print/finger_print.d
	${RM} ../bytes/read.o 
	${RM} ../bytes/read.d
	${RM} ../bytes/write.o
	${RM} ../bytes/write.d

# END
