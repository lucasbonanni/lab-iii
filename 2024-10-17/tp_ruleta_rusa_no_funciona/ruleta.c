
/*
1- La cantidad de jugadores es siempre 6.
2- Borrar los mensajes anteriores para empezar de 0.
3- Elije, en forma aleatoria, un número del 1 al 6 y lo guarda en memoria local.
4- Le envía un mensaje a cada JUGADOR, EVT_INICIO. (MSG_JUGADOR+i).
5- Espera recibir mensajes de los JUGADORES.
EVT_DISPARO, NUMERO_ELEGIDO.
• Si NUMERO_ELEGIDO recibido es diferente al número del punto 3, contesta al JUGADOR
con EVT_SALVADO. (msg.int_rte). Sigue con el punto 6.
• Si NUMERO_ELEGIDO recibido es igual al número del punto 3, el “juego” finaliza; se envía un
mensaje EVT_FIN, NRO_JUGADOR (“eliminado”) a todos los JUGADORES
(MSG_JUGADOR+i). Sigue con el punto 7.
6- Repite desde el punto 5.
7- Finaliza

Utilizar las funciones de colas.c para enviar y recibir mensajes.
*/

#include "colas.h"
#include "def.h"
#include "global.h"
#include "hilos.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int id_cola_mensajes, numero, i, done = 0, resultado_mensaje = -1;
    mensaje *msg = (mensaje *)malloc(sizeof(mensaje));
    id_cola_mensajes = creo_id_cola_mensajes();
    srand(time(NULL));
    numero = rand() % 6 + 1;
    borrar_mensajes(id_cola_mensajes);
    printf("Numero elegido: %d\n", numero);
    // Wait for EVT_READY messages from all jugadores

    while (resultado_mensaje == -1)
    {
        resultado_mensaje = recibir_mensaje(id_cola_mensajes, msg, 0);
        printf("resultado mensaje %d\n", resultado_mensaje);
        usleep(100 * 1000);
        if (msg->int_evento == EVT_INICIO)
        {
            printf("Se recibe mensaje EVT_NINGUNO del jugador %d\n", i);
            break;
        }
        system("clear");
    }
    usleep(100 * 3000);
    // Send EVT_INICIO messages to all jugadores
    for (i = 0; i < CANT_JUGADORES; i++)
    {
        msg->int_evento = EVT_INICIO;
        msg->numero_jugador = MSG_JUGADOR + i;
        msg->mtype = MSG_JUGADOR + i;
        printf("Se envia mensaje EVT_INICIO al jugador %d\n", MSG_JUGADOR + i);
        enviar_mensaje(id_cola_mensajes, msg);
    }

    while (done == 0)
    {
        recibir_mensaje(id_cola_mensajes, msg, MSG_REVOLVER);
        printf("Se recibe mensaje EVT_DISPARO del jugador %d\n", msg->numero_jugador);
        switch (msg->int_evento)
        {
        case EVT_DISPARO:
            if (msg->numero_elegido != numero)
            {
                msg->int_evento = EVT_SALVADO;
                msg->mtype = msg->numero_jugador;
                printf("Se envia mensaje EVT_SALVADO al jugador %d\n", msg->numero_jugador);
                enviar_mensaje(id_cola_mensajes, msg);
            }
            else
            {
                msg->int_evento = EVT_FIN;
                msg->mtype = msg->numero_jugador;
                printf("Se envia mensaje EVT_FIN al jugador %d\n", msg->numero_jugador);
                enviar_mensaje(id_cola_mensajes, msg);
                done = 1;
            }
            break;
        default:
            system("clear");
        }
    }

    return 0;
}
