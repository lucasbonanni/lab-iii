CC= gcc
CFLAGS= -Wall -std=gnu89 -pedantic-errors 

FFILES= clave.c colas.c global.c hilos.c jugador_threads.c
PCFILES= ruleta.c
JCFILES= jugador.c
HEADERS= -I ./

all: clean ruleta jugador

ruleta: ruleta.c
	$(CC) -o ruleta $(PCFILES) $(FFILES) $(CFLAGS) $(HEADERS)

jugador: jugador.c
	$(CC) -o jugador $(JCFILES) $(FFILES) $(CFLAGS) $(HEADERS) -pthread

clean:
	rm -rf *o jugador ruleta
