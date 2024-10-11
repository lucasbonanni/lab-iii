#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include "memoria.h"

int main(int argc, char *argv[])
{
    int id_memoria;
    void *ptr_memoria;
    int *puntero;
    int i;
    int clave_base = 33;
    int size = 10 * sizeof(int);

    ptr_memoria = creo_memoria(size, &id_memoria, clave_base);
    puntero = (int *)ptr_memoria;

    for (i = 0; i < 10; i++)
    {
        printf("%d", puntero[i]);
        usleep(100);
    }
    shmdt(ptr_memoria);

    printf("Memoria compartida creada con id: %d\n", id_memoria);
    printf("Puntero a memoria compartida: %p\n", ptr_memoria);

    return 0;
}
