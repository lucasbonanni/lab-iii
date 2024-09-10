#include <stdio.h>
#include "def.h"

void* consumer(void* arg) {
    while (1) {
        // Wait for the semaphore to be available
        sem_wait(&semaphore);

        // Critical section: read from the buffer
        if (buffer_index > 0) {
            char item = buffer[--buffer_index];
            printf("Consumed: %c\n", item);
        }

        // Signal the semaphore
        sem_post(&semaphore);

        // Sleep for a while
        usleep(INTERVALO_CONSUMER * 1000);
    }
    return NULL;
}
