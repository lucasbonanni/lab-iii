#include "thread_jugador.h"
#include "definiciones.h"
#include "funciones.h"
#include "global.h"
#include "hilos.h"
#include "colas.h"

int calcular_pasos(int tipo_animal)
{
    int pasos;
    srand(time(NULL));
    pasos = 0;
    switch (tipo_animal)
    {
    case CONEJO:
        pasos = (rand() % (9 - 4 + 1)) + 4;
        break;
    case GATO:
        pasos = (rand() % (10 - 1 + 1)) + 1;
        break;
    case PERRO:
        pasos = (rand() % (8 - 1 + 3)) + 3;
        break;
    default:
        break;
    }
    return pasos;
}



void *ThreadJugador(void *parametro)
{
    int nro_jugador;
    int id_cola_mensajes;
    int tipo_animal;
    int res;
    int done = 0;
    int pasos = 0;
    mensaje msg;

    tjugador *datos_thread = (tjugador *)parametro;
    nro_jugador = datos_thread->nro_jugador;
    id_cola_mensajes = datos_thread->id_colamensaje;
    tipo_animal = datos_thread->tipo_animal;

    printf("Jugador:%d\n", MSG_JUGADOR + nro_jugador);
    pasos = calcular_pasos(tipo_animal);
    while (done == 0)
    {
        bloquear_mutex(&mutex);
        printf("\nJugador:%d Avancé %d pasos!\n", MSG_JUGADOR + nro_jugador, pasos);
        
        res = enviar_mensaje(id_cola_mensajes, MSG_PISTA, MSG_JUGADOR + nro_jugador, EVT_CORRO, pasos);
        if (res == -1) {
            perror("Error sending message");
        }
        desbloquear_mutex(&mutex);
        usleep(100 * 8000);
        
    
        res = recibir_mensaje(id_cola_mensajes, MSG_JUGADOR + nro_jugador, &msg);
        if (res != -1) {
            //printf("Jugador:%d Recibido evento %d\n", MSG_JUGADOR + nro_jugador, msg.int_evento);
            switch (msg.int_evento) {
                case EVT_FIN:
                    printf("Jugador finaliza: %d\n", MSG_JUGADOR + nro_jugador);
                    done = 1;
                    break;
                default:
                    printf("\nJugador:%d Evento sin definir [%d]\n", MSG_JUGADOR + nro_jugador, msg.int_evento);
                    break;
            }
        } else {
            //perror("Error al recibir mensaje");
        }
    };
    pthread_exit((void *)"Listo");
}
