/*
Para evitar que todas disparen juntas se deberá usar un MUTEX, del global.h, para proteger el acceso al vector_tambor.
1- Espera recibir el mensaje EVT_INICIO.
2- Escribir por pantalla, “Soy el jugador N y voy a dispararme“
3- Envía al REVOLVER el EVT_DISPARO, NUMERO_ELEGIDO; este número lo saca del
“vector_tambor”, de uno por vez (es decir, donde no hay un 0), después pone esa posición en 1.
vector_tambor=>[1][0][0][0][0][0].
4- Escribir por pantalla, “Soy el jugador N y la posición del tambor es M“
5- Espera recibir mensajes del REVOLVER.
6- SI recibe un mensaje EVT_SALVADO, devuelve si se “salvó”-
7- Si recibe un mensaje EVT_FIN, devuelve el número del JUGADOR “eliminado” al main.
*/

#include "colas.h"
#include "def.h"
#include "global.h"
#include "hilos.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int procesar_mensaje(mensaje *msg, int id_cola_mensaje) {
    int numero_jugador, numero_elegido, done = 0;
    mensaje *rta;
    numero_jugador = msg->numero_jugador;
    rta = (mensaje *)malloc(sizeof(mensaje));

    switch (msg->int_evento) {
        case EVT_INICIO:
            printf("Soy el jugador %d y voy a lanzar\n", numero_jugador);
            printf("Soy el jugador %d y la posición del tambor es %d\n", numero_jugador, msg->int_evento);
            numero_elegido = rand() % 6 + 1;
            /*Enviar mensaje al REVOLVER*/
            bloquear_mutex(&mutex);
            rta->int_evento = EVT_DISPARO;
            rta->numero_elegido = numero_elegido;
            rta->numero_jugador = numero_jugador;
            rta->mtype = MSG_REVOLVER;
            printf("Cola id: %d, jugador: %d, evento: %d\n", id_cola_mensaje, numero_jugador, rta->int_evento);
            enviar_mensaje(id_cola_mensaje, rta);
            desbloquear_mutex(&mutex);
            usleep(100 * 100);
            done = 0;
            break;
        case EVT_SALVADO:
            printf("Jugador salvado: %d\n", msg->int_evento);
            /*Thread exit */
            pthread_exit((void *)(intptr_t)numero_jugador);
            done = 1;
            break;
        case EVT_FIN:
            printf("Jugador eliminado: %d\n", msg->int_evento);
            /*Thread exit */
            pthread_exit((void *)(intptr_t)numero_jugador);
            done = 1;
            break;
        default:
            perror("Error al recibir el mensaje\n");
            //exit(1);
    }
    return 0;
}

void *hilo_jugador(void *arg)
{
    jugador *datos_thread = (jugador*) arg;
    long numero_jugador = 0, done, id_cola_mensaje;
    mensaje msg;
    printf("Hilo jugador: %d\n", datos_thread->numero_jugador);
    id_cola_mensaje = datos_thread->id_colamensaje;
    numero_jugador = datos_thread->numero_jugador;
    done = 0;
    while (1)
    {
        printf("Esperando mensaje de inicio jugador: %ld \n", numero_jugador);
        recibir_mensaje(id_cola_mensaje, &msg, numero_jugador);
        printf("Recibido evento: %d \n", msg.int_evento);
        procesar_mensaje(&msg, id_cola_mensaje);
    }
    return NULL;
}
