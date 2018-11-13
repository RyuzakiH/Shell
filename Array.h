#include <stdio.h>

typedef struct Array
{
	int(*Length)(void **arr);
	void(*Remove)(char **arr, int index, int count);
};

int array_length(void** arr);
void array_remove(char **arr, int index, int count);

struct Array Array;