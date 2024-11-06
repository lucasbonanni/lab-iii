#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "colas.h"
#include "global.h"
#include "memoria.h"
#include "semaforo.h"
#include "clave.h"


int procesar_mensaje(int id_cola_mensajes, mensaje msg, int pasos[], int meta, int avance_humo)
{
	int nro_jugador;
	int done = 0;
	nro_jugador = msg.int_rte - MSG_MOSQUITO;
	if (nro_jugador < 0 || nro_jugador >= MSG_MOSQUITO) {
        return done;
    }
	pasos[nro_jugador] += msg.metros;
	if (pasos[nro_jugador] <= avance_humo)
	{
		enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO + nro_jugador, MSG_ESPIRAL, EVT_FIN, 2);
		printf("%d Has muerto!", MSG_MOSQUITO + nro_jugador);
		done = 1;
	}
	switch (msg.int_evento)
	{
	case EVT_AVANZO:
		pasos[nro_jugador] += msg.metros;
		printf("Jugador %d lleva %d pasos\n", MSG_MOSQUITO + nro_jugador, pasos[nro_jugador]);
		if (pasos[nro_jugador] >= meta)
		{
			enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO + nro_jugador, MSG_ESPIRAL, EVT_SOBREVIVIO, 2);
			
			printf("%d Has ganado!", MSG_MOSQUITO + nro_jugador);
			done = 1;
		}
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
	int pasos[MSG_MOSQUITO];
	int avance_humo = 0;
	int done = 0;
	mensaje msg;
	srand(time(NULL));
	meta = 95;
	memset(pasos, 0, sizeof(pasos));
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes);
	printf("Pista espiral\n");

	usleep(100 * 8000);
	while (done == 0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_ESPIRAL, &msg);
		done = procesar_mensaje(id_cola_mensajes, msg, pasos, meta, avance_humo);
		usleep(100 * 3000);
		avance_humo += rand() % (H_HASTA - H_DESDE) + H_DESDE;
		printf("\nEl humo avanza %d metros\n", avance_humo);
	}

	for (i = 0; i < MSG_MOSQUITO; i++) {
    	enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO + i, MSG_ESPIRAL, EVT_FIN, 0);
	}

	usleep(100 * 15000);
	borrar_mensajes(id_cola_mensajes);
	borrar_cola_de_mensajes(id_cola_mensajes);
	return 0;
}
