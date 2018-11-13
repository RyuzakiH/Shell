#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "bool.h"

struct Process
{
	int(*Fork)(void(*childFunc)(), bool waitToEnd, bool piping, void *args);
};

int process_fork(void(*childFunc)(), bool waitToEnd, bool piping, void *args);

struct Process Process;
