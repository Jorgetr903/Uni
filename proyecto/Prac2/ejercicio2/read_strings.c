#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

/** Loads a string from a file.
 *
 * file: pointer to the FILE descriptor
 *
 * The loadstr() function must allocate memory from the heap to store
 * the contents of the string read from the FILE.
 * Once the string has been properly built in memory, the function returns
 * the starting address of the string (pointer returned by malloc())
 *
 * Returns: !=NULL if success, NULL if error
 */
char *loadstr(FILE *file)
{
    int currentChar;
    size_t strLength = 0;
    char *str = NULL;

    // Find the length of the string
    while ((currentChar = fgetc(file)) != EOF && currentChar != '\0')
    {
        strLength++;
    }

    // Check for EOF without encountering '\0'
    if (currentChar == EOF && strLength == 0)
    {
        return NULL;
    }

    // Reset file position indicator
    fseek(file, -((long)strLength + 1), SEEK_CUR);

    // Allocate memory for the string
    str = (char *)malloc((strLength + 1) * sizeof(char));

    // Read the string into memory
    fread(str, sizeof(char), strLength, file);

    // Null-terminate the string
    str[strLength] = '\0';

    // Consume the "NULL" separator
    fseek(file, 1, SEEK_CUR);

    // Return the starting address of the string
    return str;
}

int main(int argc, char *argv[])
{
	FILE* file=NULL;
	char *str = NULL;

	if (argc!=2) {
		fprintf(stderr,"Usage: %s <file_name>\n",argv[0]);
		exit(1);
	}

	/* Open file */
	if ((file = fopen(argv[1], "r")) == NULL)
		err(2,"The input file %s could not be opened",argv[1]);

	// Load string from file
    
	while ((str = loadstr(file)) != NULL) {
        printf("%s\n", str);
		free(str);
	}

    // Free allocated memory
    free(str);

	fclose(file);
	return 0;
}
