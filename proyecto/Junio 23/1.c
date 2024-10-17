#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

//void sinR();

int main(int argc, char const *argv[])
{
    int rAvailable = 0;

    int opt;
    while ((opt = getopt(argc, argv, "R")) != -1)
	{
		switch (opt)
		{
		case 'R':
			rAvailable = 1;
			break;
		default:
			exit(EXIT_FAILURE);
		}
	}

    char directorio = NULL;

    if (optind < argc) {
        directorio = argv[optind];
    }

    if(!rAvailable){
        sinR(directorio);
    }
    else{
        conR();
    }

    return 0;
}


void conR(){
    DIR* currDirec = NULL;

    currDirec = opendir(".");

    printf("%s:\n", ".");

    struct dirent * entrada;

    char *dir = ".";
    sinR(".");


    while((entrada = readdir(currDirec)) != NULL){
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0){
            if(entrada->d_type == DT_DIR){
            int pid = fork();

            if(pid == 0){
                char ruta_completa[256];
			    snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", ".", entrada->d_name);
                printf("la ruta es %s\n", ruta_completa);
                sinR(ruta_completa);
            }
            else{
                wait(NULL);
            }
        }
        }
        
    }
    closedir(currDirec);
}



void sinR(char* directorio){

    DIR* currDirec = NULL;

    if(directorio == NULL){
        currDirec = opendir(".");   //abres el actual 

        struct dirent *entrada;

        while((entrada = readdir(currDirec)) != NULL){
            printf("%s\n", entrada->d_name);
        }

    }
    else{
        currDirec = opendir(directorio);   //abres el actual 

        struct dirent *entrada;

        while((entrada = readdir(currDirec)) != NULL){
            printf("%s\n", entrada->d_name);
        }
    }
    
}