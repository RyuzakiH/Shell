#include "Array.h"

// 8lat Fa45, Needs to be removed
int array_length(void** arr)
{
	for (int length = 0; 1; length++)
		if (arr[length] == NULL)
			return length - 1;
}

void array_remove(char **arr, int index, int count)
{
	int size = array_length(arr);

	for (int c = index; c < size; c++)
	{
		if (c + count > size - 1)
			arr[c] = NULL;
		else
			arr[c] = arr[c + count];
	}
}

struct Array Array = { array_length, array_remove };