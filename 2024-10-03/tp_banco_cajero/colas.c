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
    int resultado;
    resultado = msgsnd(id_cola, msg, sizeof(msg), 0);
    if (resultado == -1)
    {
        perror("Error al enviar el mensaje\n");
        exit(1);
    }
    return resultado;
}

int recibir_mensaje(int id_cola, mensaje *msg)
{
    int resultado;
    resultado = msgrcv(id_cola, msg, sizeof(msg), 0, 0);
    if (resultado == -1)
    {
        perror("Error al recibir el mensaje\n");
        exit(1);
    }
    return resultado;
}

int borrar_mensajes(int id_cola_mensajes)
{
    mensaje msg;
    int res;
    do
    {
        res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_evento) + sizeof(msg.char_mensaje), 0, IPC_NOWAIT);
    } while (res > 0);
    return res;
}

void borrar_cola_de_mensajes(int Id_Cola_Mensajes)
{
    msgctl(Id_Cola_Mensajes, IPC_RMID, (struct msqid_ds *)NULL);
}
