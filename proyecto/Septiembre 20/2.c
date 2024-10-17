#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>  // Incluir este header para usar intptr_t

#define NUM_THREADS 5

char shared_array[NUM_THREADS];
int current_index = 0;
pthread_mutex_t m;
pthread_cond_t cB, cC, cD, cE;

void* A(void* arg);
void* B(void* arg);
void* C(void* arg);
void* D(void* arg);
void* E(void* arg);

int main() {
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cB, NULL);
    pthread_cond_init(&cC, NULL);
    pthread_cond_init(&cD, NULL);
    pthread_cond_init(&cE, NULL);

    pthread_create(&threads[0], NULL, A, (void*)(intptr_t)'A');
    pthread_create(&threads[1], NULL, B, (void*)(intptr_t)'B');
    pthread_create(&threads[2], NULL, C, (void*)(intptr_t)'C');
    pthread_create(&threads[3], NULL, D, (void*)(intptr_t)'D');
    pthread_create(&threads[4], NULL, E, (void*)(intptr_t)'E');

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Contenido del array compartido: ");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%c ", shared_array[i]);
    }
    printf("\n");

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&cB);
    pthread_cond_destroy(&cC);
    pthread_cond_destroy(&cD);
    pthread_cond_destroy(&cE);

    return 0;
}

void write_to_shared_array(char id) {
    pthread_mutex_lock(&m);
    shared_array[current_index] = id;
    current_index++;
    pthread_mutex_unlock(&m);
}

void* A(void* arg) {
    char id = (char)(intptr_t)arg;
    printf("Soy el hilo %c\n", id);
    write_to_shared_array(id);

    pthread_mutex_lock(&m);
    pthread_cond_signal(&cB);
    pthread_cond_signal(&cC);
    pthread_mutex_unlock(&m);

    return NULL;
}

void* B(void* arg) {
    char id = (char)(intptr_t)arg;

    pthread_mutex_lock(&m);
    while (current_index < 1) {
        pthread_cond_wait(&cB, &m);
    }
    pthread_mutex_unlock(&m);

    printf("Soy el hilo %c\n", id);
    write_to_shared_array(id);

    pthread_mutex_lock(&m);
    pthread_cond_signal(&cD);
    pthread_mutex_unlock(&m);

    return NULL;
}

void* C(void* arg) {
    char id = (char)(intptr_t)arg;

    pthread_mutex_lock(&m);
    while (current_index < 1) {
        pthread_cond_wait(&cC, &m);
    }
    pthread_mutex_unlock(&m);

    printf("Soy el hilo %c\n", id);
    write_to_shared_array(id);

    pthread_mutex_lock(&m);
    pthread_cond_signal(&cD);
    pthread_cond_signal(&cE);
    pthread_mutex_unlock(&m);

    return NULL;
}

void* D(void* arg) {
    char id = (char)(intptr_t)arg;

    pthread_mutex_lock(&m);
    while (current_index < 3) {  // Espera a que B y C se ejecuten
        pthread_cond_wait(&cD, &m);
    }
    pthread_mutex_unlock(&m);

    printf("Soy el hilo %c\n", id);
    write_to_shared_array(id);

    pthread_mutex_lock(&m);
    pthread_cond_signal(&cE);
    pthread_mutex_unlock(&m);

    return NULL;
}

void* E(void* arg) {
    char id = (char)(intptr_t)arg;

    pthread_mutex_lock(&m);
    while (current_index < 4) {  // Espera a que D se ejecute
        pthread_cond_wait(&cE, &m);
    }
    pthread_mutex_unlock(&m);

    printf("Soy el hilo %c\n", id);
    write_to_shared_array(id);

    return NULL;
}
