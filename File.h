#include <stdio.h>
#include <stdlib.h>

#define CHUNK 8192

typedef struct File
{
	long(*GetFileSize)(FILE *file);
	char*(*Read)(char *filename);
	char**(*ReadLines)(char *filename, int *lines_num);
	void(*Write)(char *filename, char *data, char *mode);
};

long file_getsize(FILE *file);
char *file_read(char *filename);
char **file_readlines(char *filename, int *lines_num);
void file_write(char *filename, char *data, char *mode);

struct File File;