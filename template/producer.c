#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "def.h"

void* producer(void* arg) {
    while (1) {
        // Produce an item
        char item = 'A' + (rand() % 26); // Random letter

        // Wait for the semaphore to be available
        sem_wait(&semaphore);

        // Critical section: write to the buffer
        if (buffer_index < BUFFER_SIZE) {
            buffer[buffer_index++] = item;
            printf("Produced: %c\n", item);
        }

        // Signal the semaphore
        sem_post(&semaphore);

        // Sleep for a while
        usleep(INTERVALO_PRODUCER * 1000);
    }
    return NULL;
}
