#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct argHilos {
	int hilos_num;
	char prioridad;
};

void *thread_usuario(void *arg)
{
	struct argHilos* args = (struct argHilos*)arg;
    
    // Copiar argumentos en variables locales
    int hilos_num = args->hilos_num;
    char prioridad = args->prioridad;
    
    // Liberar la memoria dinámica reservada para los argumentos
	free(args);
	// Cuando solo hay una variable para el argumento de todos los hilos no se libera memoria, ya que la comparten
    
    // Obtener el identificador del hilo
    pthread_t hiloId = pthread_self();
    
    // Imprimir mensaje con el identificador, número de hilo y prioridad
    printf("Hilo %lu: Número de hilo: %d, Prioridad: %c\n", hiloId, hilos_num, prioridad);
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		perror("Numero de hilos incorrecto");
		exit(1);
	}

    int num_hilos = atoi(argv[1]);

    pthread_t hilos[num_hilos];
    
    for (int i = 0; i < num_hilos; i++) {
        // Crear una estructura para los argumentos del hilo
        struct argHilos* args = (struct argHilos*)malloc(sizeof(struct argHilos));
        
        // Asignar valores a los argumentos
        args->hilos_num = i;
        args->prioridad = (i % 2 == 0) ? 'P' : 'N';
        
        // Crear el hilo y pasarle los argumentos
        if (pthread_create(&hilos[i], NULL, thread_usuario, args) != 0) {
            fprintf(stderr, "Error al crear el hilo %d\n", i);
            exit(1);
        }
    }

	/*
	struct argHilos args; // Una sola variable para todos los hilos

    for (int i = 0; i < num_hilos; i++) {
        args.hilos_num = i;
        args.prioridad = (i % 2 == 0) ? 'P' : 'N';
        
        if (pthread_create(&hilos[i], NULL, thread_usuario, &args) != 0) {
            fprintf(stderr, "Error al crear el hilo %d\n", i);
            exit(1);
        }
    }
    */

    // Esperar a que los hilos finalicen
    for (int i = 0; i < num_hilos; i++) {
        if (pthread_join(hilos[i], NULL) != 0) {
            fprintf(stderr, "Error al esperar al hilo %d\n", i);
            exit(1);
        }
    }
    
    return 0;
}

/*
Hilo 140013476079360: Número de hilo: 0, Prioridad: P
Hilo 140013383710464: Número de hilo: 2, Prioridad: P
Hilo 140013467686656: Número de hilo: 1, Prioridad: N
Hilo 140013459293952: Número de hilo: 3, Prioridad: N
Hilo 140013375211264: Número de hilo: 4, Prioridad: P
Hilo 140013366818560: Número de hilo: 5, Prioridad: N
Hilo 140013358425856: Número de hilo: 6, Prioridad: P

Cuando solo hay una variable para el argumento de todos los hilos:
Hilo 139797448673024: Número de hilo: 1, Prioridad: N
Hilo 139797423494912: Número de hilo: 4, Prioridad: P
Hilo 139797415102208: Número de hilo: 5, Prioridad: N
Hilo 139797431887616: Número de hilo: 3, Prioridad: N
Hilo 139797398210304: Número de hilo: 6, Prioridad: P
Hilo 139797440280320: Número de hilo: 3, Prioridad: N
Hilo 139797406709504: Número de hilo: 6, Prioridad: P
*/
