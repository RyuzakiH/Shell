#include <stdio.h>


typedef struct Pipe
{
	char*(*Read)(int pipefd);
};

char* pipe_read(int pipefd);

struct Pipe Pipe;