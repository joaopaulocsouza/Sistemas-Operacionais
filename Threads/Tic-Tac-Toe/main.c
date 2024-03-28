#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_P1, sem_P2, sem_P3;

void *P1(void *arg) {
    while (1) {
        sem_wait(&sem_P1);
        printf("TIC ");
        sem_post(&sem_P2);
    }
    return NULL;
}

void *P2(void *arg) {
    while (1) {
        sem_wait(&sem_P2);
        printf("TAC ");
        sem_post(&sem_P3);
    }
    return NULL;
}

void *P3(void *arg) {
    while (1) {
        sem_wait(&sem_P3);
        printf("TOE ");
        sem_post(&sem_P1);
    }
    return NULL;
}

int main() {
    pthread_t thread_P1, thread_P2, thread_P3;

    sem_init(&sem_P1, 0, 1); 
    sem_init(&sem_P2, 0, 0);
    sem_init(&sem_P3, 0, 0);

    pthread_create(&thread_P1, NULL, P1, NULL);
    pthread_create(&thread_P2, NULL, P2, NULL);
    pthread_create(&thread_P3, NULL, P3, NULL);

    // Aguarda as threads
    pthread_join(thread_P1, NULL);
    pthread_join(thread_P2, NULL);
    pthread_join(thread_P3, NULL);

    sem_destroy(&sem_P1);
    sem_destroy(&sem_P2);
    sem_destroy(&sem_P3);

    return 0;
}