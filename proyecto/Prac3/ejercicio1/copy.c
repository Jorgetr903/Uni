#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define tamBuffer 512

void copy(int fdo, int fdd)
{
	int bytesRead;
	char buffer[tamBuffer];
	while ((bytesRead = read(fdo, buffer, tamBuffer)) > 0)
	{
		if (write(fdd, buffer, bytesRead) < bytesRead)
		{
			perror("escritura mal hecha");
			close(fdo);
			close(fdd);
			exit(1);
		}
	}

	if (bytesRead < 0)
	{
		perror("error al leer");
		close(fdo);
		close(fdd);
		exit(1);
	}
	close(fdo);
	close(fdd);
	exit(0);
}

int main(int argc, char *argv[])
{

	int origen = open(argv[1], O_RDONLY);
	if (origen < 0)
	{
		perror("Archivo origen no abierto");
		exit(1);
	}

	int destino = open(argv[2], O_WRONLY|O_CREAT,0751);	//sin 0751 da acceso denegado
	if (destino < 0)
	{
		close(origen);
		perror("archivo destino falla");
		exit(1);
	}

	copy(origen, destino);

	return 0;
}