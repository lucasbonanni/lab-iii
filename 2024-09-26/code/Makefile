CC=gcc
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89
PHEADER = -I ./
FFILES =  clave.c semaforo.c archivos.c memoria.c


all: clean escritura lectura

escritura: escritura.c
	$(CC) -o escritura escritura.c $(FFILES) $(CFLAGS) $(PHEADER)

lectura: lectura.c
	$(CC) -o lectura lectura.c $(FFILES) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *o lectura escritura
