#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

#define M 10

sem_t *sem_mtx; /* semáforo para control de acceso a la memoria compartida */
sem_t *cook_queue; /* cola para el cocinero */
sem_t *sav_queue; /* cola para los salvajes */

struct info {
    int servings; // porciones disponibles en la olla
    int cook_waiting; /* # de hilos bloqueados en cook_queue (0 o 1) */
    int nr_sav_waiting; /* # de salvajes bloqueados */
};

int finish = 0;

void putServingsInPot2() {
    printf("%s\n", "Let me cook");
}

void putServingsInPot(struct info *m) {
    sem_wait(sem_mtx);

    while (m->servings > 0) {   //espera a que la olla esté vacía
        m->cook_waiting++;
        sem_post(sem_mtx); // libera semáforo
        sem_wait(cook_queue); // espera
        sem_wait(sem_mtx);
    }

    m->servings = M;    //repone
    putServingsInPot2();

    printf("%d\n", m->servings);

    while (m->nr_sav_waiting > 0) {
        sem_post(sav_queue);        //avisa a los salvajes
        m->nr_sav_waiting--;
    }

    sem_post(sem_mtx);
}

void cook(struct info *m) {
    while (!finish) {
        putServingsInPot(m);
    }
}

void handler(int signo) {
    finish = 1;
    unlink("info");

    sem_close(sem_mtx);
    sem_unlink("mtx");
    sem_close(cook_queue);
    sem_unlink("cookQ");
    sem_close(sav_queue);
    sem_unlink("savQ");
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    struct sigaction old;
     sa.sa_handler = handler;

     sigaction(SIGTERM, &sa, &old);
     sigaction(SIGINT, &sa, &old);

    int Fd = open("info", O_CREAT | O_RDWR, 0666);
    if (Fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftruncate(Fd, sizeof(struct info));

    struct info *m = (struct info *)mmap(NULL, sizeof(struct info), PROT_WRITE | PROT_READ, MAP_SHARED, Fd, 0);

    if (m == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    m->cook_waiting = 0;
    m->nr_sav_waiting = 0;
    m->servings = 0;

    sem_mtx = sem_open("mtx", O_CREAT, 0644, 1);
    cook_queue = sem_open("cookQ", O_CREAT, 0644, 0);
    sav_queue = sem_open("savQ", O_CREAT, 0644, 0);

    if (sem_mtx == SEM_FAILED || cook_queue == SEM_FAILED || sav_queue == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    cook(m);

    munmap(m, sizeof(struct info));
    close(Fd);
    unlink("info");

    sem_close(sem_mtx);
    sem_unlink("mtx");
    sem_close(cook_queue);
    sem_unlink("cookQ");
    sem_close(sav_queue);
    sem_unlink("savQ");

    return 0;
}

/*
gcc -o 2 2.c
gcc -pthread -o 2 2.c
gcc -pthread -g -o 2 2.c

./2
gdb ./2

(gdb) run -> iniciar ejecución
(gdb) break fun -> establecer punto interrupción en una fución específica
(gdb) break main.c:10 -> en una línea específica
(gdb) continue -> ejecutar hasta el siguiente punto interrupción
(gdb) step -> paso a paso (entrando en funciones)
(gdb) next -> paso a paso (sin entrar en funciones)
(gdb) print variable_name
(gdb) quit -> salir

*/