#pragma once

#include <stdio.h>
#include <string.h>

#include "bool.h"

struct String
{
	//char*(*Copy)(char *dst_str, char *src_str);
	bool(*Equals)(char *string1, char *string2);
	size_t(*IndexOf)(char *string, char c);
	bool(*Contains)(char *string, char c);
	size_t(*Count)(char *string, char c);
	char**(*Split)(char *string, const char *delimiter, int *tokens_count, char*(*childFunc)());
	char*(*Trim)(char *string);
	//char*(*Replace)(char *string, char *old, char *with)
};

bool str_equals(char *string1, char *string2);
size_t str_indexof(char *string, char c);
bool str_contains(char *string, char c);
size_t str_count(char *string, char c);
char **str_split(char *string, char* delimiter, int *tokens_count, char*(*forEachFunc)());
char *str_trim(char *string);

extern struct String String;