#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include "clave.h"
#include "def.h"
#include "colas.h"

int creo_id_cola_mensajes(void)
{
    int id_cola, clave;
    clave = crear_clave_ipc(CLAVE_BASE);
    id_cola = msgget(clave, IPC_CREAT | 0600);
    if (id_cola == -1)
    {
        perror("Error al crear la cola de mensajes\n");
        exit(1);
    }
    return id_cola;
}

int enviar_mensaje(int id_cola, mensaje *msg)
{
    mensaje mensaje;
    int resultado;
    mensaje.int_evento = msg->int_evento;
    mensaje.numero_elegido = msg->numero_elegido;
    mensaje.numero_jugador = msg->numero_jugador;
    resultado = msgsnd(id_cola, (struct msgbuf *)&mensaje, sizeof(msg->int_evento) + sizeof( msg->numero_elegido) + sizeof( msg->numero_jugador), IPC_NOWAIT);

    return resultado;
}

int recibir_mensaje(int id_cola, mensaje *msg, long mtype)
{
    mensaje mensaje;
    int resultado;
    resultado = msgrcv(id_cola, (struct msgbuf *)&mensaje, sizeof(msg->int_evento) + sizeof( msg->numero_elegido) + sizeof( msg->numero_jugador) , mtype, 0);

    msg->int_evento = mensaje.int_evento;
    msg->numero_elegido = mensaje.numero_elegido;
    msg->numero_jugador = mensaje.numero_jugador;

    return resultado;
}


int borrar_mensajes(int id_cola_mensajes)
{
	mensaje msg;
	int res;
	do
	{
		res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_evento) + sizeof(msg.numero_elegido) +sizeof(msg.numero_jugador), 0, IPC_NOWAIT);
	} while (res > 0);
	return res;
}

void borrar_cola_de_mensajes(int Id_Cola_Mensajes)
{
	msgctl (Id_Cola_Mensajes, IPC_RMID, (struct msqid_ds *)NULL);
}
