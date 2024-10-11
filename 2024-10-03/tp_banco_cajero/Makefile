CC=gcc
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89
PHEADER = -I ./
FFILES =  clave.c colas.c func.c semaforo.c


all: clean banco cajero

banco: banco.c
	$(CC) -o banco banco.c $(FFILES) $(CFLAGS) $(PHEADER)

cajero: cajero.c
	$(CC) -o cajero cajero.c $(FFILES) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *o cajero banco
