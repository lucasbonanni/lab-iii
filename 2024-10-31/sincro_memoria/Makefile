CC= gcc
CFLAGS= -Wall -std=gnu89 -pedantic-errors 

FFILES= clave.c memoria.c semaforo.c
PCFILES= principal.c
JCFILES= secundario.c
HEADERS= -I ./

all: clean principal secundario

principal: principal.c
	$(CC) -o principal $(PCFILES) $(FFILES) $(CFLAGS) $(HEADERS)

secundario: secundario.c
	$(CC) -o secundario $(JCFILES) $(FFILES) $(CFLAGS) $(HEADERS)

clean:
	rm -rf *o secundario principal
