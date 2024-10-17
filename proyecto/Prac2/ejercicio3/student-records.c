#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <getopt.h>
	#include "defs.h"

	/* Assume lines in the text file are no larger than 100 chars */
	#define MAXLEN_LINE_FILE 100

	int print_text_file(char *path)
	{

		// gcc student-records.c -o studentRecords -g
		//./studentRecords -i students-db.txt -p

		student_t student;
		char *buffer;
		char *nifAux;
		char *bufferTam;
		buffer = malloc(MAXLEN_LINE_FILE);
		FILE *file = fopen(path, "r");
		if (file == NULL)
		{
			perror("Error al abrir el archivo");
			return 1;
		}

		bufferTam = malloc(4);
		fgets(bufferTam, 4, file);

		while (fgets(buffer, MAXLEN_LINE_FILE, file) != NULL) // meto en buffer toda la linea
		{
			student.student_id = atoi(strsep(&buffer, ":")); // atoi pasar de puntero de char a int
			nifAux = (strsep(&buffer, ":"));				 // pq strsep devuelve puntero a char
			strcpy(student.NIF, nifAux);					 // hagocopia
			student.first_name = (strsep(&buffer, ":"));
			student.last_name = (strsep(&buffer, ":"));

			// fscanf(file, "%d:%19[^:]%s:%49[^:]%s:%49[^:]", &student.student_id, &student.NIF, student.first_name, student.last_name);

			printf("student_id: %d\n", student.student_id);
			printf("NIF: %s\n", student.NIF);
			printf("first_name: %s\n", student.first_name);
			printf("last_name: %s\n", student.last_name);
			printf("\n");
			free(buffer);					   // libero memoria
			buffer = malloc(MAXLEN_LINE_FILE); // reservo memoria
		}
		free(buffer);
		return 0;
	}

	char *loadstr2(FILE *file)
	{
		int carac, k = 0;
		while ((carac = getc(file)) != '\0')
		{
			k++;
		}
		fseek(file, -k - 1, SEEK_CUR);

		char *ptr = malloc(k + 1);

		size_t bytesRead = fread(ptr, sizeof(char), k, file);
		fseek(file, 1, SEEK_CUR);
		return ptr;
	}




	int print_binary_file(char *path)
	{
		FILE *file = fopen(path, "r");
		int tam;
		char *token = malloc(MAXLEN_LINE_FILE);
		int id;
		char *nifAux;
		student_t student;
		fread(&tam, sizeof(int), 1, file);

		for (int i = 0; i < tam; i++)
		{
			printf("[Entry # %d]\n", i);
			fread(&id, sizeof(int), 1, file);
			student.student_id = id;

			token = loadstr2(file);
			nifAux = token;
			strcpy(student.NIF, nifAux);

			token = loadstr2(file);
			student.first_name = token;

			token = loadstr2(file);
			student.last_name = token;

			printf("\tstudent_id: %d\n", student.student_id);
			printf("\tNIF: %s\n", student.NIF);
			printf("\tfirst_name: %s\n", student.first_name);
			printf("\tlast_name: %s\n", student.last_name);
			printf("\n");
		}

		return 0;
	}

	int write_binary_file(char *input_file, char *output_file)
	{
		student_t student;
		char *buffer;
		int *tamBuffer;
		int *tamBufferP;
		char *nifAux;
		int tam;
		buffer = malloc(MAXLEN_LINE_FILE);
		tamBuffer = malloc(sizeof(int));
		FILE *file = fopen(input_file, "r");
		FILE *fileOut = fopen(output_file, "wb");

		if (file == NULL)
		{
			perror("Error al abrir el archivo");
			return 1;
		}

		fgets(tamBuffer, sizeof(tamBuffer), file);
		tam = atoi(tamBuffer);
		fwrite(&tam, sizeof(int), 1, fileOut);

		while (fgets(buffer, MAXLEN_LINE_FILE, file) != NULL) // meto en buffer toda la linea
		{

			char* cad=buffer;
			int id = atoi((strsep(&cad, ":"))); // atoi pasar de puntero de char a int
			//int * id = student.student_id;
			nifAux = (strsep(&cad, ":"));                 // pq strsep devuelve puntero a char
			strcpy(student.NIF, nifAux);                     // hagocopia
			student.first_name = (strsep(&cad, ":"));
			student.last_name = (strsep(&cad, ":"));
			student.last_name[strlen(student.last_name)-1]='\0';

			fwrite(&id, sizeof(int), 1, fileOut);

			fwrite(student.NIF, strlen(student.NIF)+1, 1, fileOut);

			fwrite(student.first_name, strlen(student.first_name)+1, 1, fileOut);

			fwrite(student.last_name, strlen(student.last_name)+1, 1, fileOut);
		}
		printf("%d student records writen successfully to binary file students-db.bin\n", atoi(tamBuffer));
		
		free(buffer);
		free(tamBuffer);
		return 0;
	}

	int main(int argc, char *argv[])
	{
		int ret_code, opt;
		struct options options;

		/* Initialize default values for options */
		options.input_file = NULL;
		options.output_file = NULL;
		options.action = NONE_ACT;
		ret_code = 0;
		FILE *file;
		int a;

		/* Parse command-line options (incomplete code!) */
		while ((opt = getopt(argc, argv, "hi:po:b")) != -1)
		{
			switch (opt)
			{
			case 'h':
				fprintf(stderr, "Usage: %s [ -h | -p | -i file | -o <output_file> | -b ]\n", argv[0]);
				exit(EXIT_SUCCESS);
			case 'i':
				options.input_file = optarg;
				break;
			case 'p':
				options.action = PRINT_TEXT_ACT; // Establecer la acción antes de entrar al bucle
				break;
			case 'o':
				options.output_file = optarg;
				options.action = WRITE_BINARY_ACT;
				break;
			case 'b':
				options.action = PRINT_BINARY_ACT;
				break;
			default:
				exit(EXIT_FAILURE);
			}
		}

		if (options.input_file == NULL)
		{
			fprintf(stderr, "Must specify one record file as an argument of -i\n");
			exit(EXIT_FAILURE);
		}

		switch (options.action)
		{
		case NONE_ACT:
			fprintf(stderr, "Must indicate one of the following options: -p, -o, -b \n");
			ret_code = EXIT_FAILURE;
			break;
		case PRINT_TEXT_ACT:
			/* Part A */
			a = print_text_file(options.input_file);

			break;
		case WRITE_BINARY_ACT:
			/* Part B */
			ret_code = write_binary_file(options.input_file, options.output_file);
			break;
		case PRINT_BINARY_ACT:
			/* Part C */
			ret_code = print_binary_file(options.input_file);
			break;
		default:
			break;
		}
		exit(ret_code);
	}