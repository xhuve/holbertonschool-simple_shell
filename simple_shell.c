#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/*
char *which(char *command)
{
	char *copy, *token, *path;
	struct stat s;

	path = getenv("PATH");

	token = strtok(path, ":");

	while(token != NULL)
	{
		copy = malloc(strlen(token) + strlen(command) + 2);
		if (copy == NULL)
			return (NULL);
		strcpy(copy, token);
		strcat(copy, "/");
		strcat(copy, command);

		if (stat(copy, &s) == 0)
			return (copy);
	}


	return (NULL);
}
*/

int main(void)
{
	while(1)
	{
		int count = 0, status;
		size_t n = 128;
		char *buff = NULL, *token, *exec_args[128];
		pid_t child_pid;

		printf("($) ");
		if (getline(&buff, &n, stdin) == -1)
		{
			perror("Error reading input");
			free(buff);
		}

		token = strtok(buff, "\n");

		while (token != NULL)
		{
	/*		if (count == 0)
				exec_args[count] = which(token);
			else */
			exec_args[count] = token;
			count++;
			token = strtok(NULL, "\n");
		}

		exec_args[count] = NULL;

		child_pid = fork();

		if (child_pid == 0)
		{
			if(exec_args[0] == NULL)
				continue;

			if(execve(exec_args[0], exec_args, NULL) == -1) 
			{
				perror("execve failed");
			}
		} else 
		{
			wait(&status);
		}
		free(buff);
		free(token);
		free(*exec_args);
	}
	return 0;
}
