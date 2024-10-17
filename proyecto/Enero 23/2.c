#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct jugador{
    int dorsal;
    int eficTiro;
    int eficRebote;
    int puntos;
};

enum estadoBalon_t{POSESION, ENAIRE};

#define MAXREBOTE 70
#define NJUGADORES 4
#define MAXPUNTOS 10
enum estadoBalon_t balon;
int dificultadRebote = 0;

struct jugador jugadores[NJUGADORES] = {
    {0,30,MAXREBOTE, 0},
    {1, 80, 20 , 0},
    {2, 40 , MAXREBOTE, 0},
    {3, 50 , 50, 0}
};
//---------------------------------------> B

int finished = 0;
int difRebote;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

void correr() {
    usleep(100);
}

void rebotear(struct jugador *j )
{
    pthread_mutex_lock(&m);

    while( (balon == ENAIRE && dificultadRebote > j->eficRebote)){
        pthread_cond_wait(&condvar, &m);
    }
    balon = POSESION;

    pthread_mutex_unlock(&m);
}

void tirar(struct jugador *j ) {
    pthread_mutex_lock(&m);
    int difTiro;
    difTiro = rand() % 100;
    if(difTiro < j->eficTiro){
        j->puntos+=2;
        if(j->puntos >= MAXPUNTOS){
        finished = 1;
        }
    }
    else{
        dificultadRebote = rand() % MAXREBOTE;
        balon = ENAIRE;
    }
    pthread_cond_broadcast(&condvar);
    pthread_mutex_unlock(&m);
}

void* jugadorInit(void* arg){
	struct jugador *j = (struct jugador *) arg;
    while (!finished) {
        rebotear(j);
        correr();
        tirar(j);
        correr();
    }
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NJUGADORES];
    for(int i = 0; i < NJUGADORES; i++){
        pthread_create(&threads[i], NULL, jugadorInit, &jugadores[i]);
    }
    for(int h = 0; h < NJUGADORES; h++){
        pthread_join(threads[h], NULL);
    }

    for(int l = 0; l < NJUGADORES; l++){
        printf("El jugador con dorsal %d, ha anotado %d puntos\n", jugadores[l].dorsal ,jugadores[l].puntos);
    }
    
    return 0;
}