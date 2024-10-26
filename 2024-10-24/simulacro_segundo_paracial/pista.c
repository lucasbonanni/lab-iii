#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "colas.h"
#include "definiciones.h"
#include "global.h"



int procesar_mensaje(int id_cola_mensajes, mensaje msg, int pasos[], int meta)
{
	int nro_jugador;
	int done = 0;
	nro_jugador = msg.int_rte - MSG_JUGADOR;
	// printf("Jugador %d, evento: %d\n", MSG_JUGADOR + nro_jugador, msg.int_evento);
	switch (msg.int_evento)
	{
	case EVT_CORRO:

		pasos[nro_jugador] += msg.pasos;
		printf("Jugador %d lleva %d pasos\n", MSG_JUGADOR + nro_jugador, pasos[nro_jugador]);
		if (pasos[nro_jugador] >= meta)
		{
			enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + nro_jugador, MSG_PISTA, EVT_FIN, 2);
			//usleep(100 * 4000);
			printf("%d Has ganado!", MSG_JUGADOR + nro_jugador);
			done = 1;
		}
		//usleep(100 * 1000);
		break;
	case EVT_FIN:
		printf("Jugador %d ha finalizado la carrera\n", MSG_JUGADOR + nro_jugador);
		done = 1;
		break;
	default:
		break;
	}
	return done;
}


int main(int argc, char *argv[])
{
	int meta;
	int id_cola_mensajes;
	int i;
	int pasos[CANT_JUGADORES] = {0};
	int done = 0;
	mensaje msg;

	meta = 117;
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes);
	printf("Pista de carrera\n");
	while (done == 0)
	{

		recibir_mensaje(id_cola_mensajes, MSG_PISTA, &msg);
		done = procesar_mensaje(id_cola_mensajes, msg, pasos, meta);
	}

	// Send EVT_FIN message to each jugador thread
	for (i = 0; i < CANT_JUGADORES; i++) {
    	enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_PISTA, EVT_FIN, 0);
	}

	usleep(100 * 15000);
	borrar_mensajes(id_cola_mensajes);
	borrar_cola_de_mensajes(id_cola_mensajes);
	return 0;
}
