#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

struct thread_args {
    int id;
    int fd;
};

void *escribirA(void *arg) {
    struct thread_args *args = (struct thread_args *)arg;
    printf("Número de hilo: %d \n", args->id);
    return NULL;
}

void *escribirB(void *arg) {
    struct thread_args *args = (struct thread_args *)arg;
    int fd = open("output.txt", O_WRONLY);
    if (fd < 0) {
        perror("Error opening file");
        return NULL;
    }

    char buffer[6];
    for (int i = 0; i < 5; i++) {
        buffer[i] = '0' + args->id;
    }
    buffer[5] = '\0';

    lseek(fd, args->id * 5, SEEK_SET);
    write(fd, buffer, 5);

    close(fd);
    return NULL;
}

void *escribirC(void *arg) {
    struct thread_args *args = (struct thread_args *)arg;

    char buffer[6];
    for (int i = 0; i < 5; i++) {
        buffer[i] = '0' + args->id;
    }
    buffer[5] = '\0';

    pthread_mutex_lock(&file_mutex);

    lseek(args->fd, args->id * 5, SEEK_SET);
    write(args->fd, buffer, 5);

    pthread_mutex_unlock(&file_mutex);
    return NULL;
}

int main(void) {
    int fd = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("Error creating file");
        return 1;
    }

    pthread_t threads[10];
    struct thread_args args[10];

    for (int i = 0; i < 10; i++) {
        args[i].id = i;
        args[i].fd = fd;
        pthread_create(&threads[i], NULL, escribirC, &args[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    // Ponemos el puntero al inicio del fichero
    lseek(fd, 0, SEEK_SET);

    char c;
    printf("File contents are:\n");
    while (read(fd, &c, 1) > 0) {
        printf("%c", (char)c);
    }
    printf("\n");

    close(fd);
    return 0;
}
