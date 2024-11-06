#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "definiciones.h"
#include "global.h"
#include "hilos.h"
#include "thread_jugador.h"
#include "colas.h"
#include "semaforo.h"
#include "memoria.h"
#include "clave.h"



int main(int argc, char *argv[])
{
	int id_cola_mensajes, i;
	pthread_t *idHilo;
	tjugador *datos_thread;
	pthread_attr_t atributos;
	
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	idHilo = (pthread_t *)malloc(sizeof(pthread_t) * CANT_MOSQUITOS);
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
	datos_thread = (tjugador *)malloc(sizeof(tjugador) * CANT_MOSQUITOS);
	
	for (i = 0; i < CANT_MOSQUITOS; i++)
	{
		datos_thread[i].nro_mosquito = i;
		datos_thread[i].id_colamensaje = id_cola_mensajes;

		pthread_create(&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
	}
	usleep(100*8000);
	for (i = 0; i < CANT_MOSQUITOS; i++)
	{
		pthread_join(idHilo[i], NULL);
		printf("Finalizo el mosquito %d \n", datos_thread[i].nro_mosquito);
		
	}
	free(datos_thread);
	pthread_attr_destroy(&atributos);
	pthread_mutex_destroy(&mutex);
	return 0;
}
