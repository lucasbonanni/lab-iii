#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "clave.h"
#include "semaforo.h"


int creo_semaforo(void)
{
    key_t clave = 0;
    int id_semaforo = 0;
    clave = creo_clave(CLAVE_BASE);
    id_semaforo = semget(clave, 1, 0600 | IPC_CREAT);
    if (id_semaforo == -1)
    {
        printf("Error: no puedo crear semaforo\n");
        exit(0);
    }
    return id_semaforo;
}

void inicia_semaforo(int id_semaforo, int valor)
{
    semctl(id_semaforo, 0, SETVAL, valor);
}

void levanta_semaforo(int id_semaforo)
{
    struct sembuf operacion;
    printf("Levanta SEMAFORO \n");
    operacion.sem_num = 0;
    operacion.sem_op = 1;
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}

void espera_semaforo(int id_semaforo)
{
    struct sembuf operacion;
    printf("Espera SEMAFORO \n");
    operacion.sem_num = 0;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}
