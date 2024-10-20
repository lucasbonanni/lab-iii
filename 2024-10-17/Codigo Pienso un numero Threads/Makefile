CC= gcc
CFLAGS= -Wall -std=gnu89 -pedantic-errors 

FFILES= hilos.c funciones.c global.c
PCFILES= pienso.c
JCFILES= jugador.c
HEADERS= -I ./

all: clean pienso jugador

pienso: pienso.c
	$(CC) -o pienso $(PCFILES) $(FFILES) $(CFLAGS) $(HEADERS)

jugador: jugador.c
	$(CC) -o jugador $(JCFILES) $(FFILES) $(CFLAGS) $(HEADERS) -pthread

clean:
	rm -rf *o jugador pienso
