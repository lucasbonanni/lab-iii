#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CLAVE_BASE 33

#define BUFFER_SIZE 100

#define ROJO 0
#define VERDE 1

#define SLEEP_DURATION 500000 

#define LARGO_NOMBRE 50

typedef struct {
    char nombre_jugador[LARGO_NOMBRE];
    int numero_pensado; // 0=indica sin número, del 1 a 99 número a verificar.
    int estado_acierto; // 0=No acierto, 1=acierto.
} juego;

#endif
