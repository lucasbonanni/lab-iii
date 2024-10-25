#include "definiciones.h"
#include "funciones.h"
#include "global.h"
#include "hilos.h"
#include "thread_jugador.h"
#include "colas.h"




int main(int argc, char *argv[])
{
	int id_cola_mensajes, i;
	pthread_t *idHilo;
	tjugador *datos_thread;
	pthread_attr_t atributos;
	
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	idHilo = (pthread_t *)malloc(sizeof(pthread_t) * CANT_JUGADORES);
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
	datos_thread = (tjugador *)malloc(sizeof(tjugador) * CANT_JUGADORES);

	for (i = 0; i < CANT_JUGADORES; i++)
	{
		datos_thread[i].nro_jugador = i;
		datos_thread[i].id_colamensaje = id_cola_mensajes;
		datos_thread[i].tipo_animal = i;

		pthread_create(&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
	}
	usleep(100*8000);
	for (i = 0; i < CANT_JUGADORES; i++)
	{
		pthread_join(idHilo[i], NULL);
		printf("Finalizo el jugador %d \n", datos_thread[i].nro_jugador);
		
	}
	free(datos_thread);
	pthread_attr_destroy(&atributos);
	pthread_mutex_destroy(&mutex);
	return 0;
}
