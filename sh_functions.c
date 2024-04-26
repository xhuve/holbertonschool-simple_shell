#include "shell.h"


void free_args(char *s[])
{
	int i = 0;

	while (s[i] != NULL)
	{
		free(*s + i);
		i++;
	}

	free(s);
}

char *_getenv(char *var)
{
	int i, len;
	char *copy;

	if (environ == NULL)
		return (NULL);

	copy = malloc(strlen(var) + 1);
	if (copy == NULL)
		return (NULL);

	strcpy(copy, var);
	strcat(copy, "=");

	len = strlen(copy);

	for (i = 0; environ[i] != NULL; i++)
	{
		if(strstr(environ[i], copy) != NULL)
		{
			free(copy);
			return (environ[i] + len);
		}
	}

	free(copy);
	return (NULL);
}

int execute(char *cmd_arr[])
{
	int status;
	pid_t child_pid;

	if ((child_pid = fork()) == 0)
	{
		if(execve(cmd_arr[0], cmd_arr, environ) == -1) 
		{
			perror("execve");
            exit(EXIT_FAILURE);
		}
	} else if (child_pid ==-1)
	{
		perror("fork");
		return (-1);
	} else
	{
		wait(&status);
	}
	
	return (0);
}

char *command_path(char *cmd)
{
	char *copy, *token, *path;
	struct stat s;

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);

	token = strtok(path, ":");

	while(token != NULL)
	{
		copy = malloc(strlen(token) + strlen(cmd) + 2);
		if (copy == NULL)
		{
			free(copy);
			return (NULL);
		}
		strcpy(copy, token);
		strcat(copy, "/");
		strcat(copy, cmd);

		if (stat(copy, &s) == 0)
		{
			return (copy);
		} else
			continue;

		free(copy);
		token = strtok(NULL, ":");
	}
	free(path); 
	return (NULL);
}


int command_tok(char *line)
{
	int count = 0;
	char *exec_args[128], *token;

	token = strtok(line, " ");

	while (token != NULL)
	{
		if (count == 0)
			exec_args[count] = command_path(token);
		else
			exec_args[count] = token;

		count++;
		token = strtok(NULL, " ");
	}

	exec_args[count] = NULL;

	return (execute(exec_args));
}
