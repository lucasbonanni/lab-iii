#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include "memoria.h"
#include "def.h"
#include "semaforo.h"

int main(int argc, char *argv[])
{
    int id_memoria; /* mover al principio del programa */
    int id_semaforo, i; /* mover al principio del método main */
    colchon *memoria = NULL; /* mover al principio del programa */
    
    id_semaforo = crear_semaforo(CLAVE_BASE);
    
    memoria = (colchon *)creo_memoria(sizeof(colchon) * MEM_REG, &id_memoria, CLAVE_BASE); /* antes del loop while */
    // 1 PIERO, 2 SUAVESTAR, 3 CANNON, 4 SIMMONS, 5 BELMO 
    memoria[0].codigo = 1;
    strcpy(memoria[0].nombre, "Piero");
    memoria[0].cantidad = 10;
    memoria[1].codigo = 2;
    strcpy(memoria[1].nombre , "Suavestar");
    memoria[1].cantidad = 10;
    memoria[2].codigo = 3;
    strcpy(memoria[2].nombre, "Cannon");
    memoria[2].cantidad = 10;
    memoria[3].codigo = 4;
    strcpy(memoria[3].nombre, "Simmons");
    memoria[3].cantidad = 10;
    memoria[4].codigo = 5;
    strcpy(memoria[4].nombre, "Belmo");
    memoria[4].cantidad = 10;
    inicializar_semaforo(id_semaforo, VERDE);
    
    while (1)
    {
        esperar_semaforo(id_semaforo);
        printf("Colchonera\n");
        for (i = 0; i < MEM_REG; i++)
        {
            if(memoria[i].cantidad < 10)
            {
                memoria[i].cantidad += 1;
            }
            printf("Colchón %s: %d unidades\n", memoria[i].nombre, memoria[i].cantidad);
        }
        /* Logica principal */
        levantar_semaforo(id_semaforo);
        usleep(SLEEP_DURATION);
        system("clear");
    }
    shmdt(memoria); /* fuera del loop while */

    return 0;
}
