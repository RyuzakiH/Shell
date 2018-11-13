#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024

typedef struct Console
{
	//char(*Read)();
	char*(*ReadLine)();
};

char *readline();

struct Console Console;;
