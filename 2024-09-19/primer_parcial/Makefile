CC=gcc
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89
PHEADER = -I ./
FFILES =  clave.c semaforo.c archivos.c


all: clean derivador caja

derivador: derivador.c
	$(CC) -o derivador derivador.c $(FFILES) $(CFLAGS) $(PHEADER)

caja: caja.c
	$(CC) -o caja caja.c $(FFILES) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *o caja derivador cajero1.txt cajero2.txt
