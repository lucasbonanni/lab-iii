/*
## Proceso Auto
- reciben por parámetro la cantidad de vías disponibles (M).
- El proceso AUTOS verifica qué vía tiene menos vehículos y suma uno a la cantidad en la vía
seleccionada. Esto lo repite cada N ms (N aleatorio entre 400 y 600ms).
- EL proceso AUTOS debe mostrar por pantalla la vía seleccionada en cada caso.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/shm.h>
#include "memoria.h"
#include "def.h"
#include "semaforo.h"

int main(int argc, char *argv[])
{
    int id_semaforo, id_memoria, i, num_vias, cant_autos, tiempo_espera;
    int *vias = NULL;
    if (argc != 2)
    {
        fprintf(stderr, "Uso: %s <número de vías>\n", argv[0]);
        exit(1);
    }

    num_vias = atoi(argv[1]);
    if (num_vias <= 0 || num_vias > MAX_VIAS)
    {
        fprintf(stderr, "El número de vías debe estar entre 1 y %d\n", MAX_VIAS);
        exit(1);
    }
    // memset(vias, 0, sizeof(int) * num_vias);
    srand(time(NULL));
    vias = (int *)creo_memoria(MAX_VIAS, &id_memoria, CLAVE_BASE);
    id_semaforo = crear_semaforo(CLAVE_BASE);
    while (1)
    {
        system("clear");
        esperar_semaforo(id_semaforo);
        for (i = 0; i < num_vias; i++)
        {
            cant_autos = rand() % 3 + 1;
            vias[i] += cant_autos;
            printf("Vía seleccionada [%d]: %d vehículos\n", i + 1, vias[i]);
            tiempo_espera = rand() % 4901 + 100; // Entre 100 y 5000 ms
            usleep(tiempo_espera * 1000);        // Convertir a microsegundos
        }
        levantar_semaforo(id_semaforo);
        // usleep(SLEEP_DURATION);
    }
    shmdt(vias);
    memset(vias, 0, sizeof(int) * num_vias);
    return 0;
}
