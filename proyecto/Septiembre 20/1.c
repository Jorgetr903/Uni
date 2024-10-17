#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int finA = 0;
int finB = 0;
int finC = 0;
int finD = 0;


pthread_cond_t cB; //finA
pthread_cond_t cC;  //finA
pthread_cond_t cD;  //finB && finC
pthread_cond_t cE;  //finD && finC

pthread_mutex_t m;


void A();
void B();
void C();
void D();
void E();

int main(int argc, char const *argv[])
{
    pthread_t threads[5];

    pthread_create(&threads[0], NULL, A, NULL);
    pthread_create(&threads[1], NULL, B, NULL);
    pthread_create(&threads[2], NULL, C, NULL);
    pthread_create(&threads[3], NULL, D, NULL);
    pthread_create(&threads[4], NULL, E, NULL);

    for(int i = 0; i < 5; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void A(){
    printf("Soy el hilo A\n");
    pthread_mutex_lock(&m);

    finA = 1;
    pthread_cond_signal(&cB);
    pthread_cond_signal(&cC);

    pthread_mutex_unlock(&m);

}

void B(){
    pthread_mutex_lock(&m);

    while(!finA){
        pthread_cond_wait(&cB, &m);
    }
    pthread_mutex_unlock(&m);

    printf("Soy el hilo B\n");


    pthread_mutex_lock(&m);

    finB = 1;
    pthread_cond_signal(&cD);

    pthread_mutex_unlock(&m);

}
void C(){
    pthread_mutex_lock(&m);

    while(!finA){
        pthread_cond_wait(&cC, &m);
    }
    pthread_mutex_unlock(&m);

    printf("Soy el hilo C\n");


    pthread_mutex_lock(&m);

    finC = 1;
    pthread_cond_signal(&cD);
    pthread_cond_signal(&cE);


    pthread_mutex_unlock(&m);
}
void D(){
    pthread_mutex_lock(&m);

    while(!finB || !finC){
        pthread_cond_wait(&cD, &m);
    }
    pthread_mutex_unlock(&m);

    printf("Soy el hilo D\n");


    pthread_mutex_lock(&m);

    finD = 1;
    pthread_cond_signal(&cE);

    pthread_mutex_unlock(&m);

}

void E(){
    pthread_mutex_lock(&m);

    while(!finD || !finC){
        pthread_cond_wait(&cE, &m);
    }
    pthread_mutex_unlock(&m);

    printf("Soy el hilo E\n");
}