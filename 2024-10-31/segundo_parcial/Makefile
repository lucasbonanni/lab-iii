CC= gcc
CFLAGS= -Wall -std=gnu89 -pedantic-errors 

FFILES= hilos.c global.c clave.c colas.c thread_jugador.c memoria.c semaforo.c
PCFILES= espiral.c
JCFILES= mosquito.c
HEADERS= -I ./

all: clean espiral mosquito

espiral: espiral.c
	$(CC) -g -o espiral $(PCFILES) $(FFILES) $(CFLAGS) $(HEADERS) -pthread

mosquito: mosquito.c
	$(CC) -g -o mosquito $(JCFILES) $(FFILES) $(CFLAGS) $(HEADERS) -pthread

clean:
	rm -rf *o mosquito espiral
