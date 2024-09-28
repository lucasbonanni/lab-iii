CC=gcc
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89
PHEADER = -I ./
FFILES =  clave.c semaforo.c memoria.c


all: clean pienso jugador

pienso: pienso.c
	$(CC) -o pienso pienso.c $(FFILES) $(CFLAGS) $(PHEADER)

jugador: jugador.c
	$(CC) -o jugador jugador.c $(FFILES) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *o jugador pienso
