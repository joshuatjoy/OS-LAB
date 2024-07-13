#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MaxItems 5    // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5  // Size of the buffer

sem_t empty;          // Semaphore to count empty slots in the buffer
sem_t full;           // Semaphore to count full slots in the buffer
int in = 0;           // Index for the next insertion in the buffer
int out = 0;          // Index for the next removal from the buffer
int buffer[BufferSize];  // Shared buffer

pthread_mutex_t mutex;  // Mutex to protect critical section
int i;                  // Global loop counter (not ideal, but used here for simplicity)

void *producer(void *pno) {
    int item;
    for (i = 0; i < MaxItems; i++) {
        item = rand();  // Produce a random item

        sem_wait(&empty);             // Wait for an empty slot
        pthread_mutex_lock(&mutex);   // Lock the critical section

        buffer[in] = item;
        printf("Producer %d: Produced Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize;  // Update index in a circular manner

        pthread_mutex_unlock(&mutex); // Unlock the critical section
        sem_post(&full);              // Signal that a full slot is available
    }
}

void *consumer(void *cno) {
    for (i = 0; i < MaxItems; i++) {
        sem_wait(&full);               // Wait for a full slot
        pthread_mutex_lock(&mutex);    // Lock the critical section

        int item = buffer[out];
        printf("Consumer %d: Consumed Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize;  // Update index in a circular manner

        pthread_mutex_unlock(&mutex);  // Unlock the critical section
        sem_post(&empty);              // Signal that an empty slot is available
    }
}

int main() {
    pthread_t pro[5], con[5];  // Thread identifiers for producers and consumers
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex

    sem_init(&empty, 0, BufferSize);  // Initialize empty semaphore with BufferSize slots
    sem_init(&full, 0, 0);            // Initialize full semaphore with 0 slots

    int a[5] = {1, 2, 3, 4, 5};  // Array for numbering producers and consumers

    // Create producer threads
    for (i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }

    // Create consumer threads
    for (i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    // Wait for all producer threads to complete
    for (i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }

    // Wait for all consumer threads to complete
    for (i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    // Destroy the mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
