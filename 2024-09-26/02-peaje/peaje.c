/*
- PEAJE posee M vías (M es recibido por parámetro) representadas por un vector en
memoria compartida.
- El proceso PEAJE atiende a una vía por vez cada N ms (N aleatorio entre 100 y 5000ms)
- Atiende siempre en un orden establecido VIA 1,2,3,4…M (y vuelve a empezar) restando un
vehículo de la vía correspondiente
- Si encuentra una vía con más de 10 vehículos en cola, deberá liberarla (pone la cantidad en 0)
- El proceso PEAJE muestra en pantalla en cada ciclo el total de vehículos en cola en cada vía:

```shell
    VIA [1]: 5 Vehículos.
    VIA [2]: 3 Vehículos.
    VIA [3]: 3 Vehículos.
```
- El PEAJE, es quien inicializa el semáforo y los datos de inicio.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "memoria.h"
#include "def.h"
#include "semaforo.h"

int num_vias;

void mostrar_estado_vias(int *vias, int num_vias)
{
    int i;
    for (i = 0; i < num_vias; i++)
    {
        printf("VIA [%d]: %d Vehículos.\n", i + 1, vias[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int *vias = NULL;
    int id_semaforo, id_memoria, i, tiempo_espera;
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
    

    srand(time(NULL));
    vias = (int *)creo_memoria(MAX_VIAS, &id_memoria, CLAVE_BASE);
    memset(vias, 0, sizeof(int) * num_vias);
    id_semaforo = crear_semaforo(CLAVE_BASE);
    inicializar_semaforo(id_semaforo, VERDE);
    while (1)
    {
        esperar_semaforo(id_semaforo);
        for (i = 0; i < num_vias; i++)
        {
            tiempo_espera = rand() % 4901 + 100; // Entre 100 y 5000 ms
            usleep(tiempo_espera * 1000);        // Convertir a microsegundos
            if (vias[i] > 10)
            {
                vias[i] = 0;
            }
            else if (vias[i] > 0)
            {
                vias[i]--;
            }
            /* Libero el SEMÁFORO. */
            levantar_semaforo(id_semaforo);
            
            usleep(SLEEP_DURATION);
            system("clear");
            mostrar_estado_vias(vias, num_vias);
        }
    }
}
