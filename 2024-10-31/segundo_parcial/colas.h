#ifndef _COLAS_H
#define _COLAS_H

#include "definiciones.h"

int creo_id_cola_mensajes(int);
int borrar_mensajes(int);
int recibir_mensaje(int, long, mensaje *);
int enviar_mensaje(int, long, int, int, int);
void borrar_cola_de_mensajes(int id_cola_mensajes);
#endif
