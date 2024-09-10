#ifndef _DEF_H
#define _DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 10
#define INTERVALO_PRODUCER 1000 // milliseconds
#define INTERVALO_CONSUMER 1000 // milliseconds

sem_t semaphore;
char buffer[BUFFER_SIZE];
int buffer_index = 0;


#endif
