# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS =
LDLIBS =

SRC = server.c client.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: server client

server: server.o
client: client.o


-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} server client

# END