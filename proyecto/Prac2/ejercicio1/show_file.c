#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[]) {
	FILE* file=NULL;
	int c,ret;

	if (argc!=2) {
		fprintf(stderr,"Usage: %s <file_name>\n",argv[0]);
		exit(1);
	}

	/* Open file */
	if ((file = fopen(argv[1], "r")) == NULL)
		err(2,"The input file %s could not be opened",argv[1]);

/* Read file byte by byte using fread */
    unsigned char buffer[1024]; // Use a buffer to store read data
    size_t bytesRead;

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        /* Write bytes to stdout using fwrite */
        ret = fwrite(buffer, 1, bytesRead, stdout);

        if (ret != bytesRead) {
            fclose(file);
            err(3, "fwrite() failed!!");
        }
    }

	if (bytesRead == 0 && ferror(file)) {
        fclose(file);
        err(4, "Error reading from file");
    }


	/* Read file byte by byte */
/*	while ((c = getc(file)) != EOF) {
		
		ret=putc((unsigned char) c, stdout);

		if (ret==EOF){
			fclose(file);
			err(3,"putc() failed!!");
		}
	}
*/
	fclose(file);
	return 0;
}
