#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "bool.h"

#include "String.h"
#include "Pipe.h"
#include "Array.h"
#include "File.h"
#include "Console.h"
#include "Process.h"
#include "Command.h"


typedef size_t size_t; // just for VS intellisense


// TODO: cat<file and similars
// TODO: add cd and history
// TODO: better interface for pipes
// TODO: manage memory


void RunShell()
{
	while (True)
	{
		if (isatty(STDIN_FILENO))
			printf("sish:> ");

		char *line = Console.ReadLine();
		
		int commandsNum;
		char **str_commands = String.Split(line, "|", &commandsNum, NULL);
		
		if (commandsNum > 1)
		{
			int pipefd = -1;

			for (int i = 0; i < commandsNum; i++)
			{
				Command command = CreateCommand();

				command.Parse(&command, String.Trim(str_commands[i]));

				command.usePiping = True;
				command.inputPipe = pipefd;

				command.Execute(&command);

				pipefd = command.outputPipe;

				if ((i == commandsNum - 1) && command.outputRedirect == False) // Last Command
				{
					char *result = Pipe.Read(command.outputPipe);
					printf("%s", result);
				}
			}
		}
		else
		{
			Command command = CreateCommand();

			command.Parse(&command, String.Trim(str_commands[0]));

			command.Execute(&command);
		}
	}

}



int main()
{
	RunShell();

	return 0;
}

