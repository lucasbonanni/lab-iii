CC= gcc
CFLAGS= -g -Wall -std=gnu89 -pedantic-errors

FFILES= archivos.c semaforo.c clave.c
GFILES= global.c 
HEADERS= -I ./

all: clean productor consumidor

productor: productor.c
	$(CC) -o productor productor.c $(FFILES) $(CFLAGS) $(HEADERS)

consumidor: consumidor.c
	$(CC) -o consumidor consumidor.c $(FFILES) $(CFLAGS) $(HEADERS)

run:
	./productor
	./consumidor

clean:
	rm -rf *o productor consumidor *.dSYM
