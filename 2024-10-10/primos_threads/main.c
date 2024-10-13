#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hilos.h"
#include <sys/time.h>

int funcion_primos(int n)
{
    int c = 0, c2 = 0, res = 0, nc = 0, total = 0;
    for (c = 1; c <= n; c++)
    {
        for (c2 = 1; c2 <= c; c2++)
        {
            res = c % c2;
            if (res == 0)
            {
                nc++;
            }
        }
        if (nc == 2)
        {
            total++;
        }
        nc = 0;
    }
    return total;
}

void *funcion_hilos(void *arg)
{
    int *n = (int *)arg;
    int total = funcion_primos(*n);
    printf("Numero de primos: %d\n", total);
    *n = total;
    salir_hilo((void *)0);
    return NULL;
}

int dif_mili(struct timeval tiempo_start, struct timeval tiempo_end)
{
    /* return (int) (fin->tv_sec - inicio->tv_sec) * 1000 + (int) (fin->tv_usec - inicio->tv_usec) / 1000; sugerido */
    int sec_start, micro_start, start, sec_end, micro_end, end;
    sec_start = tiempo_start.tv_sec & 0xFFF;
    micro_start = tiempo_start.tv_usec;
    start = sec_start * 1000 + micro_start / 1000;
    sec_end = tiempo_end.tv_sec & 0xFFF;
    micro_end = tiempo_end.tv_usec;
    end = sec_end * 1000 + micro_end / 1000;
    return end - start;
}

int main(int argc, char *argv[])
{
    char con_thread = 's';
    int i, total = 0;
    int cantidad = argc - 1;
    int *num = (int *)malloc(sizeof(int) * cantidad);

    struct timeval t_inicio, t_final;
    pthread_t *idHilo = (pthread_t *)malloc(sizeof(pthread_t) * cantidad);
    pthread_attr_t atributos;

    inicializar_atributos(&atributos);
    establecer_atributos(&atributos, PTHREAD_CREATE_JOINABLE);
    printf("PPAL: Cantidad = %d\n", cantidad);

    printf("PPAL: Con thread (s/n): ");
    scanf("%c", &con_thread);

    if(con_thread=='s')
        printf("PPAL: Con thread\n");
    else
        printf("PPAL: Sin thread\n");
    gettimeofday(&t_inicio, NULL);

    for(i = 0; i < cantidad; i++)
    {
        num[i] = atoi(argv[i + 1]);
        if(con_thread=='s')
            crear_hilo(&idHilo[i], &atributos, funcion_hilos, (void *)&num[i]);
        else
        {
            total += funcion_primos(num[i]);
            printf("Numero de primos: %d\n", total);
        }
    }

    if(con_thread=='s')
    {
        for(i = 0; i < cantidad; i++)
        {
            printf("PPAL: Esperando hilo %d\n", i);
            unir_hilo(idHilo[i], NULL);
            printf("PPAL: recibi: %d\n", num[i]);
            total += num[i];
        }
    }
    printf("PPAL: Total de primos: %d\n", total);
    gettimeofday(&t_final, NULL);
    printf("PPAL: Tiempo total: %d ms\n", dif_mili(t_inicio, t_final));
    free(idHilo);
    return 0;
}
