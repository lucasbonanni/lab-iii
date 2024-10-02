#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include "memoria.h"
#include "def.h"
#include "semaforo.h"

int main(int argc, char const *argv[])
{
    int id_semaforo; /* mover al principio del método main */
    int id_memoria; /* mover al principio del programa */
    int codigo, cantidad, resultado;
    colchon *memoria = NULL; /* mover al principio del programa */
    id_semaforo = crear_semaforo(CLAVE_BASE);
    memoria = (colchon *)creo_memoria(sizeof(colchon) * MEM_REG, &id_memoria, CLAVE_BASE); /* Definir MEM_REG en def.h antes del loop while */
    while (1)
    {
        system("clear");
        /* Solicitar por teclado el código (1 a 5) y la cantidad del colchón */
        printf("Ingrese el código del colchón y la cantidad\n");
        scanf("%d", &codigo);
        scanf("%d", &cantidad);
        esperar_semaforo(id_semaforo);
        usleep(SLEEP_DURATION);
        /* Decrementar el colchón seleccionado */
        resultado = memoria[codigo - 1].cantidad - cantidad;
        if (resultado < 0)
        {
            printf("No hay suficientes colchones %s\n", memoria[codigo - 1].nombre);
        }
        else
        {
            memoria[codigo - 1].cantidad = resultado;
        }
        levantar_semaforo(id_semaforo);
        
    }
    shmdt(memoria); /* fuera del loop while */
    return 0;
}
