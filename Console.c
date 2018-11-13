#include "bool.h"
#include "Console.h"

char *readline()
{
	int buffersize = MAX_LINE_SIZE;
	char *buffer = malloc(sizeof(char) * buffersize);

	for (int i = 0; True; i++)
	{
		char c = getchar();

		if (c == EOF)
			exit(EXIT_SUCCESS);
		else if (c == '\n')
		{
			buffer[i] = '\0';
			return buffer;
		}
		else
			buffer[i] = isspace(c) ? ' ' : c;

		if (i >= buffersize)
			buffer = realloc(buffer, (buffersize += MAX_LINE_SIZE));
	}
}

struct Console Console = { readline };
