CC=gcc
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89
PHEADER = -I ./
FFILES =  clave.c semaforo.c memoria.c


all: clean colchonera vendedor

colchonera: colchonera.c
	$(CC) -o colchonera colchonera.c $(FFILES) $(CFLAGS) $(PHEADER)

vendedor: vendedor.c
	$(CC) -o vendedor vendedor.c $(FFILES) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *o vendedor colchonera
