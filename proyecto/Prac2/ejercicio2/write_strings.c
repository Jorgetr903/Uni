#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

int main(int argc, char* argv[])
{
	FILE* file=NULL;

	if (argc < 3) {
		fprintf(stderr,"Usage: %s <file_name>\n",argv[0]);
		exit(1);
	}

	/* Open file */
	if ((file = fopen(argv[1], "wb")) == NULL)
		err(2,"The input file %s could not be opened",argv[1]);


	/* Write the provided message to the file */
	for (int i = 2; i < argc; i++) {
		size_t message_length = strlen(argv[i]);
		size_t elements_written = fwrite(argv[i], sizeof(char), message_length, file);

		if (elements_written != message_length)
        err(3, "Error writing to file");

		char terminator = '\0';
		fwrite(&terminator, sizeof(char), 1, file);
	}

	fclose(file);
	return 0;
}