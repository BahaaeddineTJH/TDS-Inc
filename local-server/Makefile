# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3
LDFLAGS =
LDLIBS =

SRC = server.c client.c queue.c shared_queue.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: server client

shared_queue.o: queue.o

../Research/dictionary.o: ../Research/dictionary.c ../Research/dictionary.h
../Research/research.o: ../Research/research.c ../Research/research.h ../Research/dictionary.o
../bytes/read.o: ../bytes/read.h ../bytes/read.c
../finger-print/finger_print.o: ../finger-print/finger_print.c ../finger-print/finger_print.h ../fourrier/fourrier.o
../fourrier/fourrier.o: ../fourrier/fourrier.c ../fourrier/fourrier.h

server: LDLIBS += -lpthread
server: server.o shared_queue.o queue.o ../Research/research.o ../bytes/read.o ../Research/dictionary.o
client: LDLIBS += -lfftw3 -lm -lsox
client: client.o ../finger-print/finger_print.o ../fourrier/fourrier.o


-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} ../Research/dictionary.o ../Research/dictionary.d
	${RM} ../Research/research.o ../Research/research.d
	${RM} ../bytes/read.o ../bytes/read.d
	${RM} ../finger-print/finger_print.o ../finger-print/finger_print.d
	${RM} ../fourrier/fourrier.o ../fourrier/fourrier.d
	${RM} server client

# END
