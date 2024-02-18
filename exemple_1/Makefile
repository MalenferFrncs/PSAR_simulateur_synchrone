all : simul boucle clean

CC=gcc
CFLAGS=-I --Wall -g
EXEC= boucle
DEPS = clauses.h macro.h topologie.h

all : boucle

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

simul:
	$(CC) $(CFLAGS) simul.c -o simul

boucle: topologie.o macro.o clauses.o boucle.o 
	$(CC) $(CFLAGS) topologie.o macro.o clauses.o boucle.o -o boucle

clean :
	rm *.o $(EXEC)
