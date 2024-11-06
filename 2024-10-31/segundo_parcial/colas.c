#include "colas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "clave.h"

int creo_id_cola_mensajes(int clave)
{
	int id_cola_mensajes = msgget(creo_clave(clave), 0600 | IPC_CREAT);
	if (id_cola_mensajes == -1)
	{
		printf("Error al obtener identificador para cola mensajes\n");
		exit(-1);
	}
	return id_cola_mensajes;
}

int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, int metros)
{
	mensaje msg;
	size_t msg_size;
	msg.long_dest = rLongDest;
	msg.int_rte = rIntRte;
	msg.int_evento = rIntEvento;
	msg.metros = metros;
	msg_size = sizeof(msg) - sizeof(msg.long_dest);
	return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg, msg_size, MSG_NOERROR | IPC_NOWAIT);
}

int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje *rMsg)
{
	mensaje msg;
	size_t msg_size;
	int res;
	msg_size = sizeof(msg) - sizeof(msg.long_dest);
	res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, msg_size, rLongDest, MSG_NOERROR | IPC_NOWAIT);

	if (res != -1)
	{
	
		rMsg->long_dest = msg.long_dest;
		rMsg->int_rte = msg.int_rte;
		rMsg->int_evento = msg.int_evento;
		rMsg->metros = msg.metros;
	}
	return res;
}

int borrar_mensajes(int id_cola_mensajes)
{
	mensaje msg;
	size_t msg_size;
	int res;
	msg_size = sizeof(msg) - sizeof(msg.long_dest);
	do
	{
		res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, msg_size, 0, IPC_NOWAIT);
	} while (res > 0);
	return res;
}

void borrar_cola_de_mensajes(int id_cola_mensajes)
{
	msgctl (id_cola_mensajes, IPC_RMID, (struct msqid_ds *)NULL);
}
