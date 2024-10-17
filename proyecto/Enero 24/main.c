#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int setargs(char *args, char **argv) {
    int count = 0;
    char *p = args;

    // Ignorar los espacios iniciales
    while (isspace((unsigned char)*p)) p++;

    // Contar subcadenas y modificar args si argv no es NULL
    if (argv != NULL) {
        argv[count] = p;
    }
    while (*p != '\0') {
        if (isspace((unsigned char)*p)) {
            *p = '\0'; // Reemplazar espacio por '\0'
            count++;
            if (argv != NULL) {
                // Saltar los espacios y asignar la próxima subcadena
                while (isspace((unsigned char)*(++p)));
                argv[count] = p;
            } else {
                while (isspace((unsigned char)*(++p)));
            }
        } else {
            p++;
        }
    }

    if (argv != NULL && argv[count] != p) {
        argv[++count] = NULL;
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Eliminar el salto de línea al final de la línea
        line[strcspn(line, "\n")] = '\0';

        // Primera llamada a setargs para contar subcadenas
        int num_args = setargs(line, NULL);

        // Reservar espacio para argv
        char **cargv = malloc((num_args + 1) * sizeof(char *));
        if (cargv == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return 1;
        }

        // Segunda llamada a setargs para llenar argv
        setargs(line, cargv);

        // Imprimir los argumentos para depuración
        printf("Command to execute: ");
        for (int i = 0; i < num_args; i++) {
            printf("%s ", cargv[i]);
        }
        printf("\n");

        // Crear nuevo proceso para ejecutar el comando
        pid_t pid = fork();
        if (pid == -1) {
            perror("Error creating process");
            free(cargv);
            fclose(file);
            return 1;
        } else if (pid == 0) {
            // Proceso hijo
            // Ejecutar el comando directamente
            execvp(cargv[0], cargv);
            perror("Error executing command");
            free(cargv);
            exit(1);
        } else {
            // Proceso padre
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("Error waiting for child process");
            } else {
                printf("Command executed with status %d\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
            }
            free(cargv);
        }
    }

    fclose(file);
    return 0;
}
