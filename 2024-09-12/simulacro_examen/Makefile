CC= gcc
CFLAGS=-Wall -std=gnu89 -pedantic-errors

FFILES=archivos.c semaforo.c clave.c
HEADERS= -I ./

all: clean avion panel

avion: avion.c
	$(CC) -o avion avion.c $(FFILES) $(CFLAGS) $(HEADERS)

panel: panel.c
	$(CC) -o panel panel.c $(FFILES) $(CFLAGS) $(HEADERS)

clean:
	rm -rf *o avion panel *.dSYM aviones.txt
