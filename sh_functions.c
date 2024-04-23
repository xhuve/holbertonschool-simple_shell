#include "shell.h"


int _printenv(void)
{
	int i, j;

	if (environ == NULL)
		return (-1);

	for(i = 0; environ[i] != NULL; i++)
	{
		printf("%s", environ[i]);
	}

	return (0);
}


char *_getenv(char *var)
{
	int i;

	if (environ == NULL)
		return (NULL);

	var = realloc(var, strlen(var) + 1);
	strcat(var, "=");

	for (i = 0; environ[i] != NULL; i++)
	{
		if(strstr(environ[i], var) != NULL)
		{
			return (environ[i]);
		}
	}

	return (NULL);
}


char *command_path(char *cmd)
{
	char *copy, *token, *path;
	struct stat s;

	path = _getenv("PATH");

	token = strtok(path, ":");

	while(token != NULL)
	{
		copy = malloc(strlen(token) + strlen(cmd) + 2);
		if (copy == NULL)
			return (NULL);

		strcpy(copy, token);
		strcat(copy, "/");
		strcat(copy, cmd);

		if (stat(copy, &s) == 0)
			return (copy);
	}

	return (NULL);
}


int execute(char *cmd_arr[])
{
	int status;
	pid_t child_pid;

	if ((child_pid = fork()) == 0)
	{
		if(execve(cmd_arr[0], cmd_arr, NULL) == -1) 
		{
			perror("execve failed");
			return (-1);
		}
	} else 
		wait(&status);
}


int command_read(char *s[])
{
	int count = 0, status;
	size_t n = 128;
	char *buff = NULL, *token;

	printf("($) ");
	if (getline(&buff, &n, stdin) == -1)
	{
		perror("Error reading input");
		free(buff);
		return (-1);
	}

	token = strtok(buff, "\t\n");

	if (strcmp(buff, "exit") == 0)
		exit(EXIT_SUCCESS);

	while (token != NULL)
	{
/*		if (count == 0)
			s[count] = command_path(token);
		else */
		s[count] = token;
		count++;
		token = strtok(NULL, "\t\n");
	}

	s[count] = NULL;

	return (0);
}
