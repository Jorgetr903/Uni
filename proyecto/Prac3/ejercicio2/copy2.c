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

void copy_regular(char *orig, char *dest)
{
}

void copy_link(char *orig, char *dest)
{
}

int main(int argc, char *argv[])
{

	int origen = open(argv[1], O_RDONLY);
	int destino = open(argv[2], O_WRONLY | O_CREAT, 0751);
	int numBytes;
	struct stat infoFile;
	lstat(argv[1], &infoFile);
	mode_t a = infoFile.st_mode;

	switch (a & S_IFMT)
	{
	case S_IFREG:
		copy(origen, destino);
		break;
	case S_IFLNK:

		numBytes = infoFile.st_size;
		char *buffer;

		buffer = malloc(numBytes + 1);
		int len = readlink(argv[1], buffer, sizeof(buffer) - 1);
		buffer[len] = '\n';

		unlink(argv[2]);
		int ret = symlink(buffer, argv[2]);
		if (ret != 0)
		{
			perror("error en el symlink");
			exit(1);
		}
		free(buffer);

		break;

	default:
		perror("no se reconoce archivo para hacer copia");
		exit(1);
	}
	return 0;
}

//  S_IFSOCK   0140000   socket
//            S_IFLNK    0120000   symbolic link
//            S_IFREG    0100000   regular file
//            S_IFBLK    0060000   block device
//            S_IFDIR    0040000   directory
//            S_IFCHR    0020000   character device
//            S_IFIFO    0010000   FIFO