/*
Proceso PIENSO: (MSG_PIENSO)

“Piensa un número”, genera en forma aleatoria un número del 1 al 99 y lo guarda en una variable local intlocal_pienso_un_numero;
Inicializa la MEMORIA COMPARTIDA y el SEMÁFORO.
Espera el semáforo.
Si numero_pensado<> 0 y estado_acierto =0
Si numero_pensado = local_pienso_un_numero. Actualiza estado_acierto = 1
Si numero_pensado<>local_pienso_un_numero. Actualiza numero_pensado = 0 y estado_acierto =0
Libero el SEMÁFORO.
Si hubo acierto, muestra por pantalla el nombre del jugador (sacarlo de MEMORIA COMPARTIDA) ganador y finaliza.
Si no hubo acierto, regresa al punto 3.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "memoria.h"
#include "def.h"
#include "semaforo.h"

int main(int argc, char const *argv[])
{
    int local_pienso_un_numero, id_semaforo, id_memoria;
    juego *memoria;
    memoria = NULL;
    /* “Piensa un número”, genera en forma aleatoria un número del 1 al 99 
        y lo guarda en una variable local intlocal_pienso_un_numero */
    srand(time(NULL));
    local_pienso_un_numero = rand() % 99 + 1;
    printf("Pienso el número: %d\n", local_pienso_un_numero);
    /* Inicializa la MEMORIA COMPARTIDA y el SEMÁFORO. */
    memoria = (juego*) creo_memoria(sizeof(juego), &id_memoria, CLAVE_BASE);
    memoria->numero_pensado = 0;
    memoria->estado_acierto = 0;
    id_semaforo = crear_semaforo(CLAVE_BASE);
    inicializar_semaforo(id_semaforo, VERDE);
    while (1)
    {
        esperar_semaforo(id_semaforo);
        /* Si numero_pensado<> 0 y estado_acierto =0 */
        if (memoria->numero_pensado != 0 && memoria->estado_acierto == 0)
        {
            /* Si numero_pensado = local_pienso_un_numero. Actualiza estado_acierto = 1 */
            if (memoria->numero_pensado == local_pienso_un_numero)
            {
                memoria->estado_acierto = 1;
                printf("Ganador: %s\n", memoria->nombre_jugador);
                break;
            }
            /* Si numero_pensado<>local_pienso_un_numero. Actualiza numero_pensado = 0 y estado_acierto =0 */
            else
            {
                memoria->numero_pensado = 0;
                memoria->estado_acierto = 0;
            }
        }
        /* Libero el SEMÁFORO. */
        levantar_semaforo(id_semaforo);
        usleep(SLEEP_DURATION);
    }
    
    return 0;
}
