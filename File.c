#include "File.h"

long file_getsize(FILE *file)
{
	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	rewind(file);
	//fseek(file, 0, SEEK_SET);

	return length;
}

char *file_read(char *filename)
{
	char *string = NULL;
	FILE *file = fopen(filename, "rb");

	if (file)
	{
		long length = file_getsize(file);

		char *buffer = malloc(CHUNK);
		string = malloc(length + 1);

		size_t read_size;
		for (int i = 0; (read_size = fread(buffer, 1, CHUNK, file)) > 0; i++)
			memcpy(string + (i * CHUNK), buffer, read_size);

		string[length] = '\0';

		if (ferror(file))
		{
			free(buffer);
			fclose(file);
			exit(EXIT_FAILURE);
		}

		free(buffer);
		fclose(file);
	}

	return string;
}

char **file_readlines(char *filename, int *lines_num)
{
	char **lines = NULL;
	FILE *file = fopen(filename, "rb");

	if (file)
	{
		long length = file_getsize(file);

		char *buffer = malloc(1024);

		lines = malloc(1000 * sizeof(char*));

		for (*lines_num = 0; fgets(buffer, 1024, file) > 0; (*lines_num)++)
		{
			lines[*lines_num] = malloc(1024 * sizeof(char));
			strcpy(lines[*lines_num], buffer);
		}

		if (ferror(file))
		{
			fclose(file);
			exit(EXIT_FAILURE); // Error
		}

		free(buffer);
		fclose(file);
	}

	return lines;
}

void file_write(char *filename, char *data, char *mode)
{
	FILE *file = fopen(filename, mode);

	if (file)
	{
		fprintf(file, "%s", data);
		fclose(file);
	}
	else
	{
		printf("Error opening file!\n");
		exit(EXIT_FAILURE);
	}
}

struct File File = { file_getsize, file_read, file_readlines, file_write };
