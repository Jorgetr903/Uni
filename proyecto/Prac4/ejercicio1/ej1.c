#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>

struct options {
	char *progname;
	int recurse;
};

struct options opt;

void usage(void)
{
	printf("%s [options] [dirname]\n\n", opt.progname);
	printf("lists the contents of dirname (default .)\n");
	printf("options:\n"
		"\t-h:\tshow this help\n"
		"\t-R:\trecursive\n"
	);
}

/* apartado b */
void list_dir(char *name)
{
	DIR *d;
    struct dirent *de;

    if ((d = opendir(name)) == NULL) {
        perror("opendir");
        return;
    }

    while ((de = readdir(d)) != NULL) {
		printf("%s\n", de->d_name);
    }
	printf("\n");

    closedir(d);
}

/* apartado c */
void process_recurse(char *dirname, char *name)
{
	pid_t pid;
    char path[PATH_MAX];

	// Formar la ruta completa del subdirectorio
    snprintf(path, sizeof(path), "%s/%s", dirname, name);
	
    if ((pid = fork()) == 0) { // Proceso hijo
        // Ejecutar el programa nuevamente con la opción -R y la ruta del subdirectorio
		execlp(opt.progname, opt.progname, "-R", path, (char *)NULL);
        perror("execlp");
        exit(1);
    } else if (pid < 0) {
        perror("fork");
    } else {
        wait(NULL); // Esperar a que el proceso hijo termine
    }
}

/* apartado c */
void list_dir_recurse(char *name)
{
	DIR *d;
	struct dirent *de;
	char path[PATH_MAX];

    if ((d = opendir(name)) == NULL) {
        perror("opendir");
        return;
    }

    while ((de = readdir(d)) != NULL) {
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {

        	if (de->d_type == DT_DIR) {
            	process_recurse(name, de->d_name);
        	}
		}
    }
    closedir(d);
}

int main(int argc, char **argv)
{
	char *dirname = ".";
	int o;
	opt.progname = argv[0];
	opt.recurse = 0;

	/* Apartado a: procesar opciones con getopt */

	while ((o = getopt(argc, argv, "hR")) != -1) {
		switch(o) {
			case 'h':
				usage();
				break;
			case 'R':
				opt.recurse = 1;
				break;
			default:
				fprintf(stderr, "Unknown option: %c\n", optopt);
                break;
		}
	}

	if (optind < argc) {
		dirname = argv[optind];
	}

	/********************************************/

	if (opt.recurse)
		printf("%s:\n", dirname);
	list_dir(dirname);

	if (opt.recurse)
		list_dir_recurse(dirname);

	return 0;
}
