#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CLAVE_BASE 33

#define BUFFER_SIZE 100

#define ROJO 0
#define VERDE 1

#define SLEEP_DURATION 500000 /* 500 ms */

#define MEM_REG 5

#define LARGO_NOMBRE 50

typedef struct {
    char nombre[LARGO_NOMBRE];
    int cantidad; 
    int codigo;
} colchon;

#endif
