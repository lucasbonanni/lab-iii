

/*
• La cantidad de jugadores es siempre 6.
• Genera un vector de 6 posiciones inicializado en 0, llamado “vector_tambor”, [0][0][0][0][0][0].
Este vector simula la posición de cada bala.
• Lanza tantos HiloJUGADOR como JUGADORES haya, y les pasa un puntero con la dirección
del “vector_tambor”.
• Se queda esperando que terminen los hilos.
• Muestra el número del JUGADOR “eliminado” por pantalla (recibido de los hilos)

Utilizar las funciones de hilos.c para crear los hilos.
Utilizar las funciones de colas.c para enviar y recibir mensajes.
Utilizar el mutex de global.c para proteger el acceso al vector_tambor.
Utilizar las funciones de jugador_threads.c para crear los hilos.
Declarar la estructura utilizada por los hilos en jugador_threads.h
*/

#include "colas.h"
#include "def.h"
#include "global.h"
#include "hilos.h"
#include "jugador_threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>





int main(int argc, char *argv[])
{
    int i, id_cola_mensajes, resultado_mensaje = 0;
    pthread_t *idHilo;
    mensaje *msg;
    jugador *datos_thread;
    pthread_attr_t 	atributos;

    idHilo = (pthread_t *)malloc(sizeof(pthread_t) * CANT_JUGADORES);
    msg = (mensaje *)malloc(sizeof(mensaje));
    datos_thread = (jugador *)malloc(sizeof(jugador) * CANT_JUGADORES);

    id_cola_mensajes= creo_id_cola_mensajes();
    
   // Send EVT_READY message
    msg->int_evento = EVT_INICIO;
    msg->mtype = MSG_REVOLVER;
    enviar_mensaje(id_cola_mensajes, msg);
    usleep(100 * 1000);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
    for (i = 0; i < CANT_JUGADORES; i++)
    {
        datos_thread[i].numero_jugador = MSG_JUGADOR + i;
        datos_thread[i].id_colamensaje = id_cola_mensajes;
        crear_hilo(&idHilo[i], &atributos, hilo_jugador, &datos_thread[i]);
    }
    for ( i = 0; i < CANT_JUGADORES; i++)
    {
        pthread_join(idHilo[i], NULL);
    }
    
    borrar_mensajes(id_cola_mensajes);
    free(idHilo);
    return 0;
}
