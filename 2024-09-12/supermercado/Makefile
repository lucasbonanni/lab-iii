CC= gcc
CFLAGS=-Wall -std=gnu89 -pedantic-errors

FFILES=archivos.c semaforo.c clave.c
HEADERS= -I ./

all: clean superderivador caja1

superderivador: super_derivador.c
	$(CC) -o super_derivador super_derivador.c $(FFILES) $(CFLAGS) $(HEADERS)

caja1: caja.c
	$(CC) -o caja1 caja.c $(FFILES) $(CFLAGS) $(HEADERS)

caja2: caja.c
	$(CC) -o caja2 caja.c $(FFILES) $(CFLAGS) $(HEADERS)

caja3: caja.c
	$(CC) -o caja3 caja.c $(FFILES) $(CFLAGS) $(HEADERS)

clean:
	rm -rf *o super_derivador caja1 caja2 caja3 *.dSYM productos.txt
	