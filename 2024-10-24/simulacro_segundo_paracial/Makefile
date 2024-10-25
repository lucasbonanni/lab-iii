CC= gcc
CFLAGS= -Wall -std=gnu89 -pedantic-errors 

FFILES= hilos.c funciones.c global.c clave.c colas.c thread_jugador.c
PCFILES= pista.c
JCFILES= jugador.c
HEADERS= -I ./

all: clean pista jugador

pista: pista.c
	$(CC) -o pista $(PCFILES) $(FFILES) $(CFLAGS) $(HEADERS)

jugador: jugador.c
	$(CC) -o jugador $(JCFILES) $(FFILES) $(CFLAGS) $(HEADERS) -pthread

clean:
	rm -rf *o jugador pista
