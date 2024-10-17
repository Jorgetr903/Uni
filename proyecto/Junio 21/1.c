#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct thread_data {
    char* name;
    int num_id;
    int order;
} thread_data_t;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int execution_order = 1;
int completed_A = 0;
int completed_B = 0;
int completed_C = 0;
int completed_D = 0;
int completed_E = 0;

void* fun(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;

    // Ejecutar sleep() fuera de la sección crítica
    int sleep_time = rand() % 3 + 1;
    sleep(sleep_time);

    // Bloquear la sección crítica para verificar y actualizar las condiciones
    pthread_mutex_lock(&mutex);

   if (strcmp(data->name, "C") == 0) {
        while (!completed_A) {
            pthread_cond_wait(&cond, &mutex);
        }
    } else if (strcmp(data->name, "D") == 0) {
        while (!completed_A || !completed_B) {
            pthread_cond_wait(&cond, &mutex);
        }
    } else if (strcmp(data->name, "E") == 0) {
        while (!completed_B) {
            pthread_cond_wait(&cond, &mutex);
        }
    } else if (strcmp(data->name, "F") == 0) {
        while (!completed_C || !completed_D) {
            pthread_cond_wait(&cond, &mutex);
        }
    } else if (strcmp(data->name, "G") == 0) {
        while (!completed_E) {
            pthread_cond_wait(&cond, &mutex);
        }
    }

    // Imprimir el mensaje fuera de la sección crítica
    pthread_mutex_unlock(&mutex);
    printf("Hilo %s con id %d\n", data->name, data->num_id);
    
    // Bloquear la sección crítica para actualizar el estado y broadcast
    pthread_mutex_lock(&mutex);
    data->order = execution_order++;

    if (strcmp(data->name, "A") == 0) {
        completed_A = 1;
    } else if (strcmp(data->name, "B") == 0) {
        completed_B = 1;
    } else if (strcmp(data->name, "C") == 0) {
        completed_C = 1;
    } else if (strcmp(data->name, "D") == 0) {
        completed_D = 1;
    } else if (strcmp(data->name, "E") == 0) {
        completed_E = 1;
    }

    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void read_names_from_file(char* filename, char* names[], int num_names) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[100];
    for (int i = 0; i < num_names && fgets(line, sizeof(line), file); i++) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        names[i] = strdup(line);
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <names_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pthread_t threads[7];
    thread_data_t thread_data[7];
    // char* names[7] = {"A", "B", "C", "D", "E", "F", "G"};
    char* names[7];
    
    read_names_from_file(argv[1], names, 7);

    for (int i = 0; i < 7; i++) {
        thread_data[i].name = names[i];
        thread_data[i].num_id = i + 1;
        thread_data[i].order = 0;
        pthread_create(&threads[i], NULL, fun, (void*)&thread_data[i]);
    }

    for (int i = 0; i < 7; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprimir el orden de terminación según el num_id
    for (int i = 0; i < 7; i++) {
        printf("%s(%d)", thread_data[i].name, thread_data[i].order);
        if (i < 6) printf("-");
    }
    printf("\n");

    // Liberar la memoria de los nombres
    for (int i = 0; i < 7; i++) {
        free(names[i]);
    }

    return 0;
}
