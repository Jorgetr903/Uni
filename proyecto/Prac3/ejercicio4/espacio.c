#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

/* Forward declaration */
int get_size_dir(char *fname, size_t *blocks);

/* Gets in the blocks buffer the size of file fname using lstat. If fname is a
 * directory get_size_dir is called to add the size of its contents.
 */
int get_size(char *fname, size_t *blocks)
{
	int tam = 0;
	struct stat infoFile;
	lstat(fname, &infoFile);

	mode_t mode = infoFile.st_mode;

	if (S_ISREG(mode))
	{
		tam += 512 * infoFile.st_blocks;
		// blocks+= infoFile.st_blocks;
		int sol = 512 * (*blocks);
		printf("%dK %s\n", tam/1000, fname);
	}
	else if (S_ISDIR(mode))
	{
		tam = get_size_dir(fname, blocks);
		printf("%dK %s\n", tam/1000, fname);
	}
	return tam;
}

/* Gets the total number of blocks occupied by all the files in a directory. If
 * a contained file is a directory a recursive call to get_size_dir is
 * performed. Entries . and .. are conveniently ignored.
 */
int get_size_dir(char *dname, size_t *blocks)
{
	DIR *directorio = opendir(dname);
	int tam = 0;
	struct dirent *entrada;

	while ((entrada = readdir(directorio)) != NULL)
	{

		if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0)
		{

			struct stat infoEntrada;
			char ruta_completa[256];
			snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", dname, entrada->d_name);
			lstat(ruta_completa, &infoEntrada);

			mode_t mode = infoEntrada.st_mode;

			if (S_ISREG(mode))
			{
				 tam += 512 * infoEntrada.st_blocks;
				//blocks += infoEntrada.st_blocks;
			}
			else if (S_ISDIR(mode))
			{
				tam += get_size_dir(entrada->d_name, blocks);
			}
		}
	}
	closedir(directorio);
	return tam;
}

/* Processes all the files in the command line calling get_size on them to
 * obtain the number of 512 B blocks they occupy and prints the total size in
 * kilobytes on the standard output
 */
int main(int argc, char *argv[])
{
	char *v = argv[1];
	int tam = get_size(argv[1], 0);

	return 0;
}