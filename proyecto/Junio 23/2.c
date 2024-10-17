#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAXCORREDORES 10

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvarPrepararse = PTHREAD_COND_INITIALIZER;
pthread_cond_t condvarCarrera = PTHREAD_COND_INITIALIZER;

int turnoActual = 0;
int esperando = 0;
int posicion = 0;

void change_clothes(int id);
int get_position(int id);
void move_position(int id, int d);
void wait_all_ready(int id);
void wait_my_turn(int id, int pos);
void run(int id, int pos);
void pass_on_relay(int id);

void *thmain(void *arg)
{
    int id = (int) (long long) arg;
    int pos;
    change_clothes(id);
    pos = get_position(id);
    move_position(id, pos);
    wait_all_ready(id);
    wait_my_turn(id, pos);
    run(id, pos);
    pass_on_relay(id);
    return NULL;
}

void change_clothes(int id){
    printf("Runner %d is changing clothes\n", id);
}

int get_position(int id){
    pthread_mutex_lock(&m);

    int dor = posicion;
    posicion++;

    pthread_mutex_unlock(&m);
    return dor;
}

void move_position(int id, int d){
    pthread_mutex_lock(&m);

    printf("Runner %d reaches its starting position %d\n", id, d);
    esperando++;
    pthread_cond_broadcast(&condvarPrepararse);
    pthread_mutex_unlock(&m);

}

void wait_all_ready(int id){
    pthread_mutex_lock(&m);

    while(esperando < MAXCORREDORES){
        pthread_cond_wait(&condvarPrepararse, &m);
    }

    pthread_mutex_unlock(&m);
}

void wait_my_turn(int id, int pos){
    pthread_mutex_lock(&m);

    while(turnoActual != pos){
        pthread_cond_wait(&condvarCarrera, &m);
    }

    pthread_mutex_unlock(&m);
}

void run(int id, int pos){
    printf("Runner %d is running from position %d\n", id, pos);
}

void pass_on_relay(int id){
    pthread_mutex_lock(&m);

    turnoActual++;
    pthread_cond_broadcast(&condvarCarrera);

    pthread_mutex_unlock(&m);
}

int main(int argc, char const *argv[]) // crea MAXCORREDORES hilos que ejecutan la funcion thmain
{
    pthread_t threads[MAXCORREDORES];

    for(int i = 0; i < MAXCORREDORES; i++){ //crea los hilos con thmain
        pthread_create(&threads[i], NULL, thmain, (void *)(long)i);
    }

    for(int h = 0; h < MAXCORREDORES; h++){// espera a que terminen
        pthread_join(threads[h], NULL);
    }

    return 0;
}

//gcc -pthread -o 2 2.c