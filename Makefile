all : boucle clean

CC=gcc
CFLAGS=-I --Wall -g
EXEC= boucle
DEPS = clauses.h topologie.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


boucle: topologie.o clauses.o boucle.o 
	$(CC) $(CFLAGS) topologie.o clauses.o boucle.o -o boucle

clean :
	del *.o $(EXEC)
