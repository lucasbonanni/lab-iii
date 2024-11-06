#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thread_jugador.h"
#include "definiciones.h"
#include "global.h"
#include "hilos.h"
#include "colas.h"


void *ThreadJugador(void *parametro)
{
    int nro_jugador;
    int id_cola_mensajes;
    int res;
    int done = 0;
    int metros = 0;
    mensaje msg;
    tjugador *datos_thread = (tjugador *)parametro;
    srand(time(NULL));
    nro_jugador = datos_thread->nro_mosquito;
    id_cola_mensajes = datos_thread->id_colamensaje;

    printf("Mozquito:%d\n", MSG_MOSQUITO + nro_jugador);
    
    
    while (done == 0)
    {
        bloquear_mutex(&mutex);
        metros = rand() % (M_HASTA - M_DESDE + 1) + M_DESDE;
        printf("\nMozquito:%d Avancé %d metros!\n", MSG_MOSQUITO + nro_jugador, metros);
        res = enviar_mensaje(id_cola_mensajes, MSG_ESPIRAL, MSG_MOSQUITO + nro_jugador, EVT_AVANZO, metros);
        if (res == -1) {
            perror("Error enviando message");
        }
        desbloquear_mutex(&mutex);
        usleep(100 * 8000);
        
    
        res = recibir_mensaje(id_cola_mensajes, MSG_MOSQUITO + nro_jugador, &msg);
        if (res != -1) {
            switch (msg.int_evento) {
                case EVT_SOBREVIVIO:
                    printf("Mozquito:%d Sobreviví!\n", MSG_MOSQUITO + nro_jugador);
                    done = 1;
                    break;
                case EVT_FIN:
                    printf("Muere mozquito: %d\n", MSG_MOSQUITO + nro_jugador);
                    done = 1;
                    break;
                default:
                    printf("\nMozquito:%d Evento sin definir [%d]\n", MSG_MOSQUITO + nro_jugador, msg.int_evento);
                    break;
            }
        } else {
            
        }
    };
    pthread_exit((void *)"Listo");
}
