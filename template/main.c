#include <pthread.h>
#include "producer.h"
#include "consumer.h"
#include "def.h"

int main(int argc, char* argv[]) {
    pthread_t producer_thread, consumer_thread;

    // Initialize the semaphore
    sem_init(&semaphore, 0, 1);

    // Create the producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (they won't in this example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}
