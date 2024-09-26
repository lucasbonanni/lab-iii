CC=gcc
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89
PHEADER = -I./
MISC1 = avion.c clave.c semaforo.c archivos.c funciones.c
MISC2 = panel.c clave.c semaforo.c archivos.c funciones.c

all: clean avion panel


avion: avion.c clave.c clave.h semaforo.c semaforo.h archivos.c archivos.c funciones.c funciones.h def.h
	$(CC) -o avion $(MISC1) $(CFLAGS) $(PHEADER)

panel: panel.c clave.c clave.h semaforo.c semaforo.h archivos.c archivos.c funciones.c funciones.h def.h
	$(CC) -o panel $(MISC2) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *o avion panel

