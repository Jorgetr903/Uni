#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define tamBuffer 1

int main(int argc, char *argv[])
{
	int opt;
	int N;
	int jump = 1;
	int origen;

	while ((opt = getopt(argc, argv, "n:e")) != -1)
	{
		switch (opt)
		{
		case 'n':
			N = atoi(optarg);
			break;
		case 'e':
			jump = 0;
			break;
		default:
			exit(EXIT_FAILURE);
		}
	}

	if (optind < argc)
	{
		origen = open(argv[optind], O_RDONLY);
	}

	char buffer[tamBuffer];
	int bytesRead;
	if (jump == 1)
	{
		lseek(origen, N, SEEK_SET);
		while ((bytesRead = read(origen, buffer, tamBuffer)) > 0)
		{
			if (write(1, buffer, bytesRead) < bytesRead)
			{
				perror("error en escritura");
				close(origen);
				exit(1);
			}
		}
	}
	else
	{


		int pos = lseek(origen, -N - 1, SEEK_END);
		
		if (pos == -1)
		{
			perror("lseek error");
			exit(1);
		}

		
	
		while ((bytesRead = read(origen, buffer, tamBuffer)) > 0)
		{
			printf("pos es %d\n",pos);
			if (write(1, buffer, bytesRead) < bytesRead)
			{
				perror("error en escritura");
				close(origen);
				exit(1);
			}
		}
	}
	close(origen);
	return 0;
}