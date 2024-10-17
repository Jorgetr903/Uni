#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

#define NUMITER 3


sem_t *sem_mtx; /* contador del semáforo se inicializa a 1 */
sem_t *cook_queue; /* contador del semáforo se inicializa a 0 */
sem_t *sav_queue; /* contador del semáforo se inicializa a 0 */

struct info{
	int servings;
	int cook_waiting; /* # bloqueados en cook_queue (0 o 1) */
	int nr_sav_waiting; /* # de salvajes bloqueados */
};



int getServingsFromPot()
{
	printf("%s", "im eating ");
}

void eat(struct info *m)
{
	unsigned long id = (unsigned long) getpid();
	printf("Savage %lu eating\n", id);
	printf("%d", m->servings);
	sleep(rand() % 5);
}

void savages(struct info *a)
{
	sem_wait(sem_mtx);

	while(a->servings == 0){
		
		if(a->cook_waiting > 0){	//si el cocinero está esperando
			sem_post(cook_queue);	//avisa al cocinero para que cocine
			a->cook_waiting--;
		}

		a->nr_sav_waiting++;		//se va a dormir
		sem_post(sem_mtx);
		sem_wait(sav_queue);
		sem_wait(sem_mtx);
		
	}

	getServingsFromPot();
	a->servings--;
	sem_post(sem_mtx);

	eat(a);
}

int main(int argc, char *argv[])
{
	// semaforos
	sem_mtx = sem_open("mtx", O_CREAT, 0644, 1);
	if (sem_mtx == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
	cook_queue = sem_open("cookQ", O_CREAT, 0644, 0);
	if (cook_queue == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
	sav_queue = sem_open("savQ", O_CREAT, 0644, 0);
	if (sav_queue == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

	// mem compartida

	int Fd = open("info", O_RDWR, 0666);
	if(Fd == -1){
		perror("necesario llamar primero al cocinero");
		exit(1);
	}

	struct info * m = (struct info *) mmap(NULL, sizeof(struct info), PROT_WRITE | PROT_READ, MAP_SHARED, Fd, 0);

	if (m == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

	//printf("%s", "parado");

	savages(m);

	// desproyectar memoria

	munmap(m, sizeof(struct info));
	close(Fd);


	sem_close(sem_mtx);	
	sem_close(cook_queue);
	sem_close(sav_queue);


	return 0;
}