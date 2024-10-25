#include "funciones.h"
#include "clave.h"


int creo_id_memoria(int size, int clave)
{
	int id_memoria;

	id_memoria = shmget(creo_clave(clave), size, 0777 | IPC_CREAT); // crea memoria x 50 byte,

	if (id_memoria == -1)
	{

		printf("No consigo id para memoria compartida\n");

		exit(0);
	}

	return id_memoria;
}

void *creo_memoria(int id_memoria)
{
	void *ptr_memoria;

	ptr_memoria = (void *)shmat(id_memoria, (char *)0, 0);

	if (ptr_memoria == NULL)
	{
		printf("No consigo memoria compartida\n");

		exit(0);
	}
	return ptr_memoria;
}

int creo_semaforo(int cuantos)
{
	key_t clave = creo_clave(CLAVE_BASE);
	int id_semaforo = semget(clave, cuantos, 0600 | IPC_CREAT);
	if (id_semaforo == -1)
	{
		printf("Error: no puedo crear semaforo\n");
		exit(0);
	}
	return id_semaforo;
}

void inicio_semaforo(int id_semaforo, int cual, int valor)
{
	semctl(id_semaforo, cual, SETVAL, valor);
}

void levanta_semaforo(int id_semaforo, int cual)
{
	struct sembuf operacion;
	operacion.sem_num = cual;
	operacion.sem_op = 1; // incrementa el semaforo en 1
	operacion.sem_flg = 0;
	semop(id_semaforo, &operacion, 1);
}

void espera_semaforo(int id_semaforo, int cual)
{
	struct sembuf operacion;
	operacion.sem_num = cual;
	operacion.sem_op = -1; // decrementa el semaforo en 1
	operacion.sem_flg = 0;
	semop(id_semaforo, &operacion, 1);
}
