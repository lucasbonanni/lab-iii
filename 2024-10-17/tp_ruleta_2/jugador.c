#include "funciones.h"
#include "definiciones.h"
#include "global.h"
#include "hilos.h"


//declaro la estructura pra ser usada por los threads
typedef struct tipo_jugador tjugador;
struct tipo_jugador
{
	int 	nro_jugador;						
	int  id_colamensaje;
	int   cant_jugadores;
};

void *ThreadJugador (void *parametro)
{
	int 			nro_jugador;
	int 			id_cola_mensajes;
	int 			done=0;
	int 			cant_jugadores;
	int 			numero;
	int 			cant_intentos;
	int 			i;
	char 	cadena[50];
	mensaje		msg;
	
	tjugador *datos_thread = (tjugador*) parametro;
	nro_jugador = datos_thread->nro_jugador;
	id_cola_mensajes = datos_thread->id_colamensaje;
	cant_jugadores = datos_thread -> cant_jugadores;
	cant_intentos=0;
	printf("Jugador:%d\n", MSG_JUGADOR + nro_jugador);
	
								      
	while(done==0)
	{
		bloquear_mutex(&mutex);
		numero = (rand()%(HASTA-DESDE+1))+DESDE;

		printf("\nJugador:%d Envia el numero:%d  A ver si le pegue!\n", MSG_JUGADOR + nro_jugador, numero);
		sprintf(cadena,"%d",numero);
		enviar_mensaje(id_cola_mensajes , MSG_REVOLVER,MSG_JUGADOR+nro_jugador, EVT_INICIO, cadena);
		cant_intentos++;
		usleep(100 * 1000);
		desbloquear_mutex(&mutex);
		
		recibir_mensaje(id_cola_mensajes, (long)MSG_JUGADOR+nro_jugador, &msg); // bloqueate

		switch (msg.int_evento)
		{
			case EVT_DISPARO:
				printf("\nAcerte: Con %d Cantidad de intentos \n", cant_intentos);
				
				// for(i=0;i<cant_jugadores;i++)
				// {
				// 	//enviar_mensaje(id_cola_mensajes , MSG_JUGADOR, MSG_JUGADOR, EVT_FIN, "FINALIZAR");
				// 	//enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_REVOLVER, EVT_FIN, "FINALIZAR");
				// 	bloquear_mutex(&mutex);
				// 	enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_JUGADOR + nro_jugador, EVT_FIN, "FINALIZAR");
				// 	usleep(100 * 3000);
				// 	desbloquear_mutex(&mutex);
				// }
				done=1;
				break;		    	
			case EVT_SALVADO:
					printf("Jugador salvado: %d \n", MSG_JUGADOR + nro_jugador);
					done=1;
				break;
			case EVT_FIN:
				printf("Jugador eliminado: %d\n", MSG_JUGADOR + nro_jugador);
				done=1;
				break;
			default:
				printf("\nJugador:%d Evento sin definir\n", MSG_JUGADOR + nro_jugador);
			break;
		}
		//sleep (1);
		usleep(100 * 1000);

	};

	pthread_exit ((void *)"Listo");
	

}


int main(int argc, char *argv[])
{
	int id_cola_mensajes, i;
	int cant_jugadores;
	pthread_t* idHilo;
	tjugador *datos_thread;
	pthread_attr_t 	atributos;
	srand(time(NULL));
	cant_jugadores = CANT_JUGADORES;
	printf("cantidad de jugadores %d \n\n", cant_jugadores);
	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);


	idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cant_jugadores);
	
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	
	datos_thread = (tjugador*) malloc(sizeof(tjugador)*cant_jugadores);
	
	for(i=0; i<cant_jugadores; i++)
	{
		datos_thread[i].nro_jugador = i;
		datos_thread[i].id_colamensaje = id_cola_mensajes;
		datos_thread[i].cant_jugadores=cant_jugadores;
		
		pthread_create (&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
	}

	for(i=0;i<CANT_JUGADORES;i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("Finalizo el jugador %d \n",datos_thread[i].nro_jugador);
		//usleep(100*1000);
	}
	
	
	free(datos_thread);
	pthread_attr_destroy(&atributos);
	pthread_mutex_destroy(&mutex);
	return 0;
}
