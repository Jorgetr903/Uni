#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <getopt.h>

#define MAX_COMMANDS 100

typedef struct {
    pid_t pid;
    int command_num;
} CommandInfo;

pid_t run_command(const char* command) {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/bash", "bash", "-c", command, NULL); //ejecuta el programa bash pasándole -c y el comando
        perror("execl failed");
        exit(1);
    }
    return pid;
}

void usage(const char* progname) {
    fprintf(stderr, "Usage: %s [-x command] [-s file] [-b]\n", progname);
    exit(1);
}

int main(int argc, char* argv[]) {
    int opt;
    char* command = NULL;
    char* script_file = NULL;
    int background = 0;

    CommandInfo commands[MAX_COMMANDS];
    int command_count = 0;

    while ((opt = getopt(argc, argv, "x:s:b")) != -1) {
        switch (opt) {
            case 'x':
                command = optarg;
                break;
            case 's':
                script_file = optarg;
                break;
            case 'b':
                background = 1;
                break;
            default:
                usage(argv[0]);
        }
    }

    if (command) {
        pid_t pid = run_command(command);
        int status;
        waitpid(pid, &status, 0);
    }

    if (script_file) {
        FILE* file = fopen(script_file, "r");
        if (!file) {
            perror("fopen failed");
            exit(1);
        }

        char line[1024];
        int command_num = 0;

        while (fgets(line, sizeof(line), file) && command_count < MAX_COMMANDS) {
            line[strcspn(line, "\n")] = 0; // remove newline
            printf("@@ Running command #%d: %s\n", command_num, line);
            pid_t pid = run_command(line);
            commands[command_count].pid = pid;
            commands[command_count].command_num = command_num;
            command_count++;
            if (!background) {
                int status;
                waitpid(pid, &status, 0);
                printf("@@ Command #%d terminated (pid: %d, status: %d)\n", command_num, pid, status);
            }
            command_num++;
        }

        fclose(file);
    }

    if (background && command_count > 0) {
        int status;
        for (int i = 0; i < command_count; i++) {
            pid_t pid = waitpid(commands[i].pid, &status, 0);
            for (int j = 0; j < command_count; j++) {
                if (commands[j].pid == pid) {
                    printf("@@ Command #%d terminated (pid: %d, status: %d)\n", commands[j].command_num, pid, status);
                    break;
                }
            }
        }
    }

    return 0;
}
