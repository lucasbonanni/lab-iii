CC=gcc
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89
PHEADER = -I ./
FFILES =  clave.c semaforo.c memoria.c


all: clean peaje autos

peaje: peaje.c
	$(CC) -o peaje peaje.c $(FFILES) $(CFLAGS) $(PHEADER)

autos: autos.c
	$(CC) -o autos autos.c $(FFILES) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *o autos peaje
