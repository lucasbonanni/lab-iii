#include "def.h"
#include "hilos.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

/*
    1.	Cada N ms (N aleatorio en 500 a 5000) genera un número al azar de 1 al 99 (no repetitivos).
    2.	Verifica la variable alguien_acerto (puntero que recibió por parámetro); si ésta es distinta de 0, significa que ya hay un ganador. En dicho caso, termina el hilo.
    3.	Compara el número generado con el que “pensó” el main (el que recibió por parámetro).
    4.	En caso de acierto, cambia el valor de la variable alguien_acerto (utilizando el puntero) por el número de jugador. Y termina el hilo.
    5.	Al finalizar el hilo, cada uno debe devolver la cantidad de intentos que tuvo.
*/
void *ThreadJugador(void *params)
{
    int i;
    ThreadParams *thread_params = (ThreadParams *)params;
    int id_jugador = thread_params->id_jugador;
    int *alguien_acerto = thread_params->alguien_acerto;
    int *intentos = thread_params->intentos;
    int *adivinar = thread_params->numero;
    /*Array the numeros pensandos */
    int *numeros_pensados = malloc(sizeof(int) * 99);
    int tiempo = rand() % 4501 + 500;
    *intentos = 0;

    while (!*alguien_acerto)
    {
        int numero = rand() % 99 + 1;
        /* Verificar si el numero ya fue pensado */
        for (i = 0; i < *intentos; i++)
        {
            if (numeros_pensados[i] == numero)
            {
                numero = rand() % 99 + 1;
                i = -1;
            }
        }
        numeros_pensados[*intentos] = numero;
        usleep(tiempo * 1000);

        (*intentos)++;
        if (*alguien_acerto)
        {
            break;
        }
        printf("Jugador %d pensó el número %d\n", id_jugador, numero);
        bloquear_mutex(&mutex);
        if (numero == *adivinar)
        {
            printf("Jugador %d acertó el número %d\n", id_jugador, numero);
            *alguien_acerto = id_jugador;
            desbloquear_mutex(&mutex);
            break;
        }
        desbloquear_mutex(&mutex);
    }

    free(numeros_pensados);
    salir_hilo((void *)intentos);
    return NULL;
}

/*
    •	Recibe por parámetro la cantidad de jugadores (argc, argv).
    •	“Piensa un número” genera en forma aleatoria un número del 1 al 99.
    •	Inicializa una variable intalguien_acerto = 0 (local del main)
    •	Lanza tantos ThreadJugadores como jugadores se hayan ingresado por parámetro; les pasa como parámetro el número que “pensó”. Además, le pasa el puntero a la variable alguien_acerto.
    •	Queda a la espera que los hilos finalicen.
    •	Al finalizar los hilos, el main debe indicar cuál es el jugador ganador.
*/
/*
    1.	Generar los hilos y sólo utilizar como variable global la de mutex. Todas las demás deben ser pasadas como parámetro desde el main al hilo.
    2.	Al finalizar el main, debe mostrar al ganador y mostrar la cantidad de intentos de cada jugador.
    3.	Evitar que haya más de un ganador.
    4.	Mostrar la actividad en forma diferenciada de cada hilo.
*/

int main(int argc, char *argv[])
{
    int numero, alguien_acerto = 0, i;
    int cantidad_jugadores;
    int *intentos;
    pthread_attr_t atributos;
    pthread_t *jugadores;
    ThreadParams *params;
    if (argc != 2)
    {
        printf("Error en la cantidad de argumentos\n");
        return 1;
    }
    cantidad_jugadores = atoi(argv[1]);
    if (cantidad_jugadores < 1)
    {
        printf("Error en la cantidad de jugadores\n");
        return 1;
    }

    inicializar_mutex(&mutex);
    inicializar_atributos(&atributos);
    establecer_atributos(&atributos, PTHREAD_CREATE_JOINABLE);
    srand(time(NULL));

    numero = rand() % 99 + 1;
    alguien_acerto = 0;

    jugadores = malloc(sizeof(pthread_t) * cantidad_jugadores);
    params = malloc(sizeof(ThreadParams) * cantidad_jugadores);
    intentos = malloc(sizeof(int) * cantidad_jugadores);
    if (jugadores == NULL || params == NULL || intentos == NULL)
    {
        printf("Error en la reserva de memoria\n");
        return 1;
    }
    while (1)
    {
        for (i = 0; i < cantidad_jugadores; i++)
        {
            params[i].id_jugador = i + 1;
            params[i].alguien_acerto = &alguien_acerto;
            params[i].intentos = &intentos[i];
            params[i].numero = &numero;
            crear_hilo(&jugadores[i], &atributos, ThreadJugador, (void *)&params[i]);
        }

        for (i = 0; i < cantidad_jugadores; i++)
        {
            unir_hilo(jugadores[i], NULL);
        }

        if (alguien_acerto != 0)
        {
            printf("El jugador %d acertó el número %d\n", alguien_acerto, numero);
            break;
        }
        else
        {
            printf("Nadie acertó el número %d\n", numero);
        }

        for (i = 0; i < cantidad_jugadores; i++)
        {
            printf("Jugador %d tuvo %d intentos\n", i + 1, intentos[i]);
        }
    }
    free(jugadores);
    free(params);
    free(intentos);
    destruir_mutex(&mutex);
    destruir_atributos(&atributos);
    return 0;
}
