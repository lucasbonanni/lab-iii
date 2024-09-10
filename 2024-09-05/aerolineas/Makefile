CC= gcc
CFLAGS=-Wall -std=gnu89 -pedantic-errors

FFILES= archivos.c semaforo.c clave.c
GFILES= global.c 
HEADERS= -I ./

all: clean cargas reservas

cargas: cargas.c
	$(CC) -o cargas cargas.c $(FFILES) $(CFLAGS) $(HEADERS)

reservas: reservas.c
	$(CC) -o reservas reservas.c $(FFILES) $(CFLAGS) $(HEADERS)

run:
	./cargas
	./reservas

clean:
	rm -rf *o cargas reservas *.dSYM
