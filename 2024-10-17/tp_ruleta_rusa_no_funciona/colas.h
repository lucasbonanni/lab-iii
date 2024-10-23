#ifndef COLAS_H
#define COLAS_H
#include "def.h"

int creo_id_cola_mensajes(void);
int enviar_mensaje(int id_cola, mensaje *msg);
int recibir_mensaje(int id_cola, mensaje *msg, long mtype);
int borrar_mensajes(int id_cola_mensajes);
void borrar_cola_de_mensajes(int Id_Cola_Mensajes);
#endif
