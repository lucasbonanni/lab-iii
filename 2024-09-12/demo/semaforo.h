#ifndef SEMAFOROS_H
#define SEMAFOROS_H

int crear_semaforo(int clave_base);

void inicializar_semaforo(int id_semaforo, int valor);

void levantar_semaforo(int id_semaforo);

void esperar_semaforo(int id_semaforo);

#endif
