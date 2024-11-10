#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
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

int main(int argc, char *argv[]) {
    int *p = NULL;
    signal(SIGINT, interrput_handler);
    signal(SIGALRM, alarm_handler);
    signal(SIGSEGV, segfault_handler);
    alarm(2);
    *p += 2;
    while (1) {
        system("clear");
        printf("Esperando señal...\n");
        sleep(1);
    }
    return 0;
}
