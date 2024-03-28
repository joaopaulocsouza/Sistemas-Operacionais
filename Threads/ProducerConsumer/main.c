#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define N 100
#define TRUE 1

typedef sem_t semaphore;
semaphore mutex;
semaphore empty;
semaphore full;

int buffer[N];
int buffer_index = 0;

// Função de produção fictícia
int produce_item() {
    return rand() % 100; // Exemplo: Número aleatório entre 0 e 99
}

// Função de consumo fictícia
void consume_item(int item) {
    printf("Consumed item: %d\n", item);
}

void insert_item(int item) {
    if (buffer_index < N) {
        buffer[buffer_index] = item;
        buffer_index++;
    }
}

int remove_item() {
    int item = -1;
    if (buffer_index > 0) {
        buffer_index--;
        item = buffer[buffer_index];
    }
    return item;
}

void *producer(void *arg) {
    int item;
    while (TRUE) {
        item = produce_item();
        sem_wait(&empty);
        sem_wait(&mutex);
        
        insert_item(item);
        
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    while (TRUE) {
        sem_wait(&full);
        sem_wait(&mutex);
        
        item = remove_item();
        
        sem_post(&mutex);
        sem_post(&empty);
        
        consume_item(item);
    }
    pthread_exit(NULL);
}

int main() {
    // Inicialização dos semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    
    pthread_t producer_thread, consumer_thread;
    
    // Criação das threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // Espera pelas threads terminarem
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    // Destruir os semáforos
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
