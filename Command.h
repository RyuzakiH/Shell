#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "bool.h"
#include "String.h"

typedef struct Command Command;
struct Command
{
	char *name;
	int argc;
	char** argv;

	bool inputRedirect;
	char *inputRedirectFilename;

	bool outputRedirect;
	char *outputRedirectFilename;

	bool background;

	bool usePiping;
	int inputPipe;
	int outputPipe;

	int(*Execute)(Command *self);

	void(*Parse)(Command *self, char *str_command);

	void(*Print_args)(Command *self);
};

char** command_extract_args(char *str_command, int *argc);
void command_parse(Command *self, char *str_command);
void command_handle_input_redirection(char *filename);
void command_handle_output_redirection(char *filename);
int command_execute_helper(Command *self);
void command_print_args(Command *self);

Command CreateCommand();