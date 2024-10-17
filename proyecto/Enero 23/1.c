#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>


void recorrer(char* outputFile, int numBytes){

    DIR* directorio = opendir(".");

    struct dirent *entrada;
    int fd;
    if(outputFile != NULL){
        fd =open(outputFile, O_WRONLY | O_CREAT, 0751);

    }

    while ((entrada = readdir(directorio)) != NULL)
	{

		if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0)
		{

			struct stat infoEntrada;
			char ruta_completa[256];
			snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", ".", entrada->d_name);
			lstat(ruta_completa, &infoEntrada);

			mode_t mode = infoEntrada.st_mode;

			if (S_ISREG(mode))
			{
                if(outputFile != NULL){
                    int numEscribir = min(numBytes, infoEntrada.st_size);
                    int fd2 = open(entrada->d_name, O_RDONLY);


                    char buffer [numEscribir];
                    int leidos = read(fd2, buffer, numEscribir);
                    if(leidos > 0){
                        write(fd, buffer, leidos);
                    write(fd, "||", 2);
                    }
                    
                }
                else{
                    int numEscribir = min(numBytes, infoEntrada.st_size);
                    int fd2 = open(entrada->d_name, O_RDONLY);


                    char buffer [numEscribir];
                    read(fd2, buffer, numEscribir);

                    printf("%s\n", buffer);
                }
			}
		}
	}
	closedir(directorio);


}


int main(int argc, char const *argv[])
{
    
    int numBytes;
    char * outPutFile = NULL;

    int opt;

    while ((opt = getopt(argc, argv, "n:o:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            numBytes = atoi(optarg);
            break;
        case 'o':
            outPutFile = optarg;
            break;
        default:
            exit(EXIT_FAILURE);
        }
    }

    recorrer(outPutFile, numBytes);


    return 0;
}