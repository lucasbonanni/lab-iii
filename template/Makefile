CC= gcc
CFLAGS= -Wall -std=gnu89 -pedantic-errors

FFILES= 

CFILES= consumer.c producer.c main.c
HEADERS= -I ./

all: clean main

main: main.c
	$(CC) -o main $(CFILES) $(FFILES) $(CFLAGS) $(HEADERS)

clean:
	rm -rf *o main
