#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "hilos.h"

pthread_mutex_t mutex;

void *funcionThread(void *parametro)
{
    int i;
    printf("Hijo\n");
    for (i = 0; i < CANTIDAD; i++)
    {
        bloquear_mutex(&mutex);
        printf("Soy el hijo y tengo el mutex\n");
        usleep(SLEEP_TIME);
        desbloquear_mutex(&mutex);
        usleep(SLEEP_TIME);
    }
    printf("Soy el hijo y espero 10 segundos\n");
    usleep(10000000);
    printf("Soy el hijo y termino\n");
    // pthread_exit((void *)0); sugerencia
    salir_hilo((void *)"Listo");
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t idHilo;
    pthread_attr_t atributos;
    int i;
    char *valorDevuelto = NULL;
    inicializar_mutex(&mutex);
    inicializar_atributos(&atributos);
    establecer_atributos(&atributos, PTHREAD_CREATE_JOINABLE);
    if(crear_hilo(&idHilo, &atributos, funcionThread, NULL) != 0)
    {
        perror("Error en pthread_create");
        exit(1);
    }
    for (i = 0; i < CANTIDAD; i++)
    {
        bloquear_mutex(&mutex);
        printf("Soy el padre y tengo el mutex\n");
        usleep(SLEEP_TIME);
        desbloquear_mutex(&mutex);
        usleep(SLEEP_TIME);
    }
    printf("Soy el padre y espero 10 segundos\n");
    unir_hilo(idHilo, (void *)&valorDevuelto);
    printf("Soy el padre Ya ha terminado el hijo\n");

    printf("El hijo termino con salida %s\n", valorDevuelto);
    destruir_mutex(&mutex);
    printf("Soy el padre y termino\n");
    return 0;
}
