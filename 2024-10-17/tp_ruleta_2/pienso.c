#include <stdio.h>
#include "funciones.h"
#include <pthread.h>
#include "definiciones.h"
#include "global.h"


int main(int argc, char *argv[])
{
	int pienso_un_numero;
	int id_cola_mensajes;
	int numero_recibido;
	int nro_jugador;
	int done = 0;
	mensaje msg;

	srand(time(NULL));
	// pienso el numero y lo guardo en la variable local
	pienso_un_numero = (rand() % (DESDE - HASTA + 1)) + DESDE;

	printf("Pense este numero %d\n", pienso_un_numero);

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes); // Borra todos los mensajes que haya en la cola.

	while (done == 0)
	{

		recibir_mensaje(id_cola_mensajes, MSG_REVOLVER, &msg); // bloqueate
		// Obtengo el id del jugador que me esta enviando el mensaje.
		nro_jugador = msg.int_rte - MSG_JUGADOR;
		printf("Pienso:%d Recibi un mensaje\n", MSG_JUGADOR + nro_jugador);

		switch (msg.int_evento)
		{
		case EVT_INICIO:

			numero_recibido = atoi(msg.char_mensaje);

			if (numero_recibido == pienso_un_numero)
			{
				//enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + nro_jugador, MSG_REVOLVER, EVT_DISPARO, "FINALIZAR");

				enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + nro_jugador, MSG_REVOLVER, EVT_DISPARO, "FINALIZAR");
				usleep(100 * 8000);
				printf("%d Has ganado! con el número %d ",MSG_JUGADOR + nro_jugador, numero_recibido);
				done = 1;
			}
			else
			{
				pthread_mutex_lock(&mutex);
				enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + nro_jugador, MSG_REVOLVER, EVT_SALVADO, "FINALIZAR");
				usleep(100 * 2000); // Espera 3 segundos
				pthread_mutex_unlock(&mutex);
				printf("Finalizar Jugador:%d ", MSG_JUGADOR + nro_jugador);
			}
			usleep(100 * 1000);
			break;
		default:
			printf("\nPienso:%d Evento sin definir\n", MSG_JUGADOR + nro_jugador);
			break;
		}
	}
	usleep(100 * 1000);

	return 0;
}
