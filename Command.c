#include "Command.h"
#include "Array.h"
#include "Process.h"

char** command_extract_args(char *str_command, int *argc)
{
	int count;
	char **tokens = String.Split(str_command, "\"", &count, NULL);

	*argc = 0;

	int max_count = String.Count(str_command, ' ');

	char **result = malloc((max_count + 1) * sizeof *result);

	for (int i = 0; i < count; i++)
	{
		if (i % 2 == 0)
		{
			int c;
			char **token = String.Split(tokens[i], " ", &c, NULL);

			for (int j = 0; j < c; j++, (*argc)++)
			{
				result[*argc] = malloc(strlen(token[j]) * sizeof(char));
				strcpy(result[*argc], token[j]);
			}
		}
		else
		{
			result[*argc] = malloc(strlen(tokens[i]) * sizeof(char));
			strcpy(result[*argc], tokens[i]);
			(*argc)++;
		}
	}

	result[*argc] = NULL;

	return result;
}

void command_parse(Command *self, char *str_command)
{
	self->argv = command_extract_args(str_command, &self->argc);

	self->name = self->argv[0];
	// cat input.txt > output.txt
	// cat < input.txt > output.txt
	for (int i = 0; i < self->argc; i++)
	{
		if (String.Equals(self->argv[i], "<")) //input redirection
		{
			self->inputRedirect = True;
			self->inputRedirectFilename = malloc(strlen(self->argv[i + 1]) * sizeof(char));
			strcpy(self->inputRedirectFilename, self->argv[i + 1]);

			if (self->inputRedirectFilename[strlen(self->inputRedirectFilename) - 1] == '!')
				self->inputRedirectFilename[strlen(self->inputRedirectFilename) - 1] = '\0';

			Array.Remove(self->argv, i--, 2);
			self->argc -= 2;
		}
		else if (String.Equals(self->argv[i], ">")) //output redirection
		{
			self->outputRedirect = True;
			self->outputRedirectFilename = malloc(strlen(self->argv[i + 1]) * sizeof(char));
			strcpy(self->outputRedirectFilename, self->argv[i + 1]);

			if (self->outputRedirectFilename[strlen(self->outputRedirectFilename) - 1] == '!')
				self->outputRedirectFilename[strlen(self->outputRedirectFilename) - 1] = '\0';

			Array.Remove(self->argv, i--, 2);
			self->argc -= 2;

			break;
		}
	}
}

void command_handle_input_redirection(char *filename)
{
	int fd = open(filename, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void command_handle_output_redirection(char *filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int command_execute_helper(Command *self)
{
	if (self->inputRedirect)
		command_handle_input_redirection(self->inputRedirectFilename);

	if (self->outputRedirect)
		command_handle_output_redirection(self->outputRedirectFilename);

	execvp(self->name, self->argv);

	perror("ERROR: Executing Command");
	exit(EXIT_FAILURE);
}

int command_execute(Command *self)
{
	//printf("Executing: %s\n", self->name);

	if (self->usePiping && self->inputPipe > 0)
		dup2(self->inputPipe, STDIN_FILENO);

	return (self->outputPipe = Process.Fork(command_execute_helper, True, self->usePiping, self)); //return output pipe fd
}

void command_print_args(Command *self)
{
	for (int i = 0; i < self->argc; i++)
		printf("%s\n", self->argv[i]);
}

Command CreateCommand()
{
	Command command;

	command.usePiping = False;
	command.inputRedirect = False;
	command.outputRedirect = False;
	command.background = False;

	command.Parse = command_parse;

	command.Execute = command_execute;

	command.Print_args = command_print_args;

	return command;
}
