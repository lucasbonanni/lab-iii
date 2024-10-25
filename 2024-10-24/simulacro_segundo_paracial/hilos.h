#ifndef HILOS_H
#define HILOS_H
#include <pthread.h>

int inicializar_mutex(pthread_mutex_t *mutex);
int bloquear_mutex(pthread_mutex_t *mutex);
int desbloquear_mutex(pthread_mutex_t *mutex);
int destruir_mutex(pthread_mutex_t *mutex);
int inicializar_atributos(pthread_attr_t *atributos);
int establecer_atributos(pthread_attr_t *atributos, int atributo);
int destruir_atributos(pthread_attr_t *atributos);
int crear_hilo(pthread_t *idHilo, pthread_attr_t *atributos, void *(*funcionThread)(void *), void *parametro);
int salir_hilo(void *valor);
int unir_hilo(pthread_t idHilo, void *valor);

#endif
