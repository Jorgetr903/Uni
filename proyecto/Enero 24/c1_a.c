#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Implementación de la función setargs
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

// Función main para pruebas
int main() {
    char input[] = "ls -l -t";
    char *argv[10]; // Suficiente espacio para los argumentos de prueba

    int num_args = setargs(input, argv);

    for (int i = 0; i < num_args; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}
