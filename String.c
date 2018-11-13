#include "String.h"

bool str_equals(char *string1, char *string2)
{
	return !strcmp(string1, string2);
}

size_t str_indexof(char *string, char c)
{
	return strchr(string, c) - string;
}

bool str_contains(char *string, char c)
{
	size_t index = str_indexof(string, c);
	return (index >= 0 && index < strlen(string));
}

size_t str_count(char *string, char c)
{
	size_t count;
	for (count = 0; *string; string++)
		count += (*string == c);
	return count;
}

char **str_split(char *string, char* delimiter, int *tokens_count, char*(*forEachFunc)())
{
	// Because of Access Violation
	char *tempstr = malloc(strlen(string) * sizeof(char));
	strcpy(tempstr, string);

	size_t count = str_count(tempstr, delimiter[0]) + 1;

	char **args = malloc(count * sizeof(char*));

	char *arg = strtok(tempstr, delimiter);
	for (*tokens_count = 0; arg != NULL; (*tokens_count)++)
	{
		if (forEachFunc)
		{
			arg = forEachFunc(arg);
			args[*tokens_count] = malloc(strlen(arg) * sizeof(char));
			args[*tokens_count] = arg;
		}
		else
		{
			args[*tokens_count] = malloc(strlen(arg) * sizeof(char));
			args[*tokens_count] = arg;
		}

		arg = strtok(NULL, delimiter);
	}

	return args;
}

char *str_trim(char *string)
{
	char *end;

	// Trim leading space
	while (isspace((unsigned char)*string)) string++;

	if (*string == 0)  // All spaces?
		return string;

	// Trim trailing space
	end = string + strlen(string) - 1;
	while (end > string && isspace((unsigned char)*end)) end--;

	// Write new null terminator character
	end[1] = '\0';

	return string;
}

struct String String = { str_equals, str_indexof, str_contains, str_count, str_split, str_trim };