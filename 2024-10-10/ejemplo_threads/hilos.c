#include <pthread.h>

int inicializar_mutex(pthread_mutex_t *mutex)
{
    return pthread_mutex_init(mutex, NULL);
}

int bloquear_mutex(pthread_mutex_t *mutex)
{
    return pthread_mutex_lock(mutex);
}

int desbloquear_mutex(pthread_mutex_t *mutex)
{
    return pthread_mutex_unlock(mutex);
}

int destruir_mutex(pthread_mutex_t *mutex)
{
    return pthread_mutex_destroy(mutex);
}

int inicializar_atributos(pthread_attr_t *atributos)
{
    return pthread_attr_init(atributos);
}

int establecer_atributos(pthread_attr_t *atributos, int atributo)
{
    return pthread_attr_setdetachstate(atributos, atributo);
}

int crear_hilo(pthread_t *idHilo, pthread_attr_t *atributos, void *(*funcionThread)(void *), void *parametro)
{
    return pthread_create(idHilo, atributos, funcionThread, parametro);
}

int salir_hilo(void *valor)
{
    pthread_exit(valor);
}

int unir_hilo(pthread_t idHilo, void **valor)
{
    return pthread_join(idHilo, valor);
}
