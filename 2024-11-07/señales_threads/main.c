#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void interrput_handler(int signum) {
    printf("\n\nSeñal recibida: %d\n", signum);
    exit(0);
}

void alarm_handler(int signum) {
    printf("\n\nSeñal recibida: %d\n", signum);
}

void segfault_handler(int signum) {
    printf("\n\nSeñal recibida: %d\n", signum);
    // print the stack trace
    printf("No me voy a morir \n");

}

void *thread_handler(void *arg) {
    // print the stack trace
    printf("No me voy a morir \n");
    while (1) {
        printf("Esperando señal...\n");
        sleep(1);
    }

}

int main(int argc, char *argv[]) {
    int *p = NULL;
    int i;
    pthread_attr_t atributos;
    pthread_t *idHilo;
    signal(SIGINT, interrput_handler);
    signal(SIGALRM, alarm_handler);
    signal(SIGSEGV, segfault_handler);
    /* Inicializar atributos threads*/
    
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    /* Allocate memory for thread IDs */
    idHilo = (pthread_t*)malloc(3 * sizeof(pthread_t));
    if (idHilo == NULL) {
        perror("Failed to allocate memory for thread IDs");
        return 1;
    }
    alarm(2);
    while (1) {
        for( i=0; i<3; i++) {
            /*Crear los threads */
            pthread_create(&idHilo[i], &atributos, &thread_handler, NULL);
        }
        sleep(1);
    }
    /* Free allocated memory */
    free(idHilo);
    return 0;
}
