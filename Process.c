#include "Process.h"

int process_fork(void(*childFunc)(), bool waitToEnd, bool piping, void *args)
{
	int pipefd[2];
	pipe(pipefd);

	pid_t pid = fork();

	if (pid == 0) // Child process
	{
		if (piping)
		{
			close(pipefd[0]);    // close reading end in the child

			dup2(pipefd[1], STDOUT_FILENO);  // send stdout to the pipe
			dup2(pipefd[1], STDERR_FILENO);  // send stderr to the pipe

			close(pipefd[1]);    // this descriptor is no longer needed
		}

		(*childFunc)(args);
	}
	else if (pid < 0) // Error forking
	{
		perror("ERROR: Error Forking");
	}
	else // Parent process
	{
		if (waitToEnd)
		{
			pid_t wpid;
			int status;

			do
			{
				wpid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));


			close(pipefd[1]);  // close the write end of the pipe in the parent

			return pipefd[0];
		}
	}
}

struct Process Process = { process_fork };
