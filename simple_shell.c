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
	int count = 0;
	size_t n = 128;
	char *buff = NULL, *token, *exec_args[128];

	printf("#cisfun$ ");
	if (getline(&buff, &n, stdin) == -1)
	{
		perror("Error reading input");
		free(buff);
		return (1);
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

	if(execve(exec_args[0], exec_args, NULL) == -1) 
	{
		perror("execve failed");
		free(buff);
		exit(EXIT_FAILURE);
	}

	return 0;
}
