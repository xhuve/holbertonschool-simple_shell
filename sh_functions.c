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
	int i, len = 0;
	char *copy;

	if (environ == NULL)
	{
		return (NULL);
	}

	copy = malloc(sizeof(char) * strlen(var) + 2);
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
	char *curr[128];

	curr[0] = cmd_arr[0];
	curr[1] = NULL;

	if ((child_pid = fork()) == 0)
	{
		if(execvp(curr[0], curr) == -1) 
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

int command_tok(char *line)
{
	int count = 0;
	char *exec_args[128], *token;

	token = strtok(line, " ");

	while (token != NULL)
	{
		exec_args[count] = token;

		count++;
		token = strtok(NULL, " ");
	}

	exec_args[count] = NULL;

	return (execute(exec_args));
}
