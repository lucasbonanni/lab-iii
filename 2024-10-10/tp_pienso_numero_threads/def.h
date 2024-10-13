#ifndef DEF_H
#define DEF_H
#include <pthread.h>

#define CANTIDAD 10
#define SLEEP_TIME 1000 /* 1000 microsegundos equivale a segundos  */

typedef struct {
    int id_jugador;
    int *alguien_acerto;
    int *intentos;
    int *numero;
} ThreadParams;

#endif
