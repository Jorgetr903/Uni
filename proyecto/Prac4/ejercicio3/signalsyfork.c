#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/*programa que temporiza la ejecución de un proceso hijo */
void alarm_handler(int signum) {
    // Se llama cuando la alarma termina
    // Se envia señal SIGKILL al proceso hijo
    kill(getpid(), SIGKILL);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Uso: %s <comando a ejecutar>\n", argv[0]);
        return 1;
	}

	int pid = fork();

	if (pid < 0) {
		perror("Error al crear el proceso hijo");
        return 1;
	}
	else if (pid == 0) { // Proceso hijo
		if (execvp(argv[1], &argv[1]) == -1) {
            perror("execvp failed");
            exit(1);
        }
	} else { // Proceso padre

		signal(SIGALRM, alarm_handler);

        alarm(5);

        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("El proceso hijo terminó normalmente con código de salida %d.\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("El proceso hijo terminó debido a una señal.\n");
        }
	}

	return 0;
}
