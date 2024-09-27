#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define CLAVE_BASE 33

#define BUFFER_SIZE 100

#define ROJO 0
#define VERDE 1

#define SLEEP_DURATION 500000 
#define PRECIO_LIMITE 20000

typedef struct {
    char descripcion[100];
    int precio;
} Producto;

#define ARCHIVO_CAJERO_1 "cajero1.txt"
#define ARCHIVO_CAJERO_2 "cajero2.txt"

#endif
