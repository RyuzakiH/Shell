#include "Pipe.h"

char* pipe_read(int pipefd)
{
	char *string = malloc(BUFSIZ);

	char buffer[BUFSIZ];

	size_t length = 0;

	for (size_t read_size; (read_size = read(pipefd, buffer, sizeof(buffer))) != 0; )
	{
		length += read_size;
		realloc(string, length + 1);
		memcpy(string + (length - read_size), buffer, read_size);
	}

	string[length] = '\0';

	return string;
}

struct Pipe Pipe = { pipe_read };