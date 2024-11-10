#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaforo.h"

#define CLAVE_BASE 33

int main(int argc, char const *argv[])
{
    int id_memoria;
    int id_semaforo;
    int i;
    int *flag;
    printf("\nSe inicializa");
    flag = (int *)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE);
    *flag = 2;
    printf("\nValor id_memoria: %d", id_memoria);
    printf("\nValor flag: %d", *flag);
    id_semaforo = crear_semaforo(CLAVE_BASE);
    inicializar_semaforo(id_semaforo,1);
    while (*flag < 3)
    {
        system("clear");
        printf("\nValor id_memoria: %d", id_memoria);
        printf("\nValor flag: %d", *flag);
        if (*flag != 1 && *flag != 3)
        {
            esperar_semaforo(id_semaforo);
            *flag = 2;
            levantar_semaforo(id_semaforo);
            usleep(10000);
        }
        if (*flag == 1)
        {
            esperar_semaforo(id_semaforo);
            *flag += 2;
            levantar_semaforo(id_semaforo);
        }
        printf("\n\nEsperando el a segundo..");
    }
    for (i = 0; i < 5; i++)
    {
        printf("\nPrincipal %d", i);
    }
    return 0;
}