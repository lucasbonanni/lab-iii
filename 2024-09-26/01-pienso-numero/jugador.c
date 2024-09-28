/*
1. Espera el semáforo.
2. Verifica de MEMORIA COMPARTIDA:
   1. Si numero_pensado = 0 y estado_acierto =0
      1. Genera un número al azar de 1 al 99 (no repetitivos).
      2. Actualiza la variable numero_pensado con el número generado.
    2. Si numero_pensado<> 0 y estada_acierto=1
        1. Acertó, muestra por pantalla la cantidad de intentos.
3. Liberar el semáforo.
4. Si no hubo acierto, repite desde el punto 1.
5. Si hubo acierto, finaliza.

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
    int local_pienso_un_numero, id_semaforo, id_memoria, intentos;
    juego *memoria;
    memoria = NULL;
    intentos = 0;
    local_pienso_un_numero = 0;
    /* Inicializa la MEMORIA COMPARTIDA y el SEMÁFORO. */
    memoria = (juego*) creo_memoria(sizeof(juego), &id_memoria, CLAVE_BASE);
    id_semaforo = crear_semaforo(CLAVE_BASE);
    srand(time(NULL));
    scanf("%s", memoria->nombre_jugador);
    while (1)
    {
        esperar_semaforo(id_semaforo);
        /* “Piensa un número”, genera en forma aleatoria un número del 1 al 99 
        y lo guarda en una variable local intlocal_pienso_un_numero */
        printf("Pienso un número\n");
        /* Si numero_pensado<> 0 y estado_acierto =0 */
        if (memoria->estado_acierto == 0)
        {
            local_pienso_un_numero = rand() % 99 + 1;
            memoria->numero_pensado = local_pienso_un_numero;
            intentos++;
            printf("Intento con el número: %d\n y numeros de intentos: %d \n", local_pienso_un_numero, intentos);
        }
        /* Libero el SEMÁFORO. */
        levantar_semaforo(id_semaforo);
        usleep(SLEEP_DURATION);
        system("clear");
        /* Si numero_pensado<> 0 y estado_acierto =1 */
        if (memoria->numero_pensado == local_pienso_un_numero && memoria->estado_acierto == 1)
        {
            printf("Adiviné! \n");
            intentos=0;
            break;
        }

    }
    return 0;
}
