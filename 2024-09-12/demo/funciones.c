#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "funciones.h"
#include "archivos.h"
#include "def.h"
#include "semaforo.h"
#include "clave.h"



void generar_nombre_aleatorio(char *nombre) {
    int idx = rand() % 25;
    char* nombres[25] = {
        "Buenos Aires", "Lima", "Madrid", "Bogotá",
        "Caracas", "Santiago", "Ciudad de México", "Brasilia", "Lisboa",
        "París", "Roma", "Londres", "Montevideo", "Ottawa",
        "Berlin", "Canberra", "Tokio", "Pekín", "Moscú",
        "Praga", "Dublín", "Atenas", "Oslo", "Ámsterdam","Shangai"};
    strcpy(nombre, nombres[idx]);
}
