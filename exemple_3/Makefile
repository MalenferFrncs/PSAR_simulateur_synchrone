all : simul boucle clean

CC=gcc
CFLAGS=-I --Wall -g
EXEC= boucle
DEPS = clauses.h macro.h make_topo.h compare_config.h make_topo.h

all: boucle 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


boucle: make_topo.o macro.o clauses.o compare_config.o boucle.o 
	$(CC) $(CFLAGS) make_topo.o macro.o clauses.o  compare_config.o boucle.o -o boucle

clean :
	rm *.o $(EXEC)
