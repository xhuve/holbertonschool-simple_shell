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

int _printenv(void)
{
	int i;

	if (environ == NULL)
		return (-1);

	for(i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}

	return (0);
}

void trim_space(char *s)
{
	int i = 0, j = 0;
	char *copy;

	copy = strdup(s);

	while (s[i] == ' ')
		i++;

	for (j = 0; s[i] != '\0'; j++)
	{
		copy[j] = s[i];
		i++;
	}
	free(copy);
}

int execute(char *cmd_arr[])
{
	int status;
	pid_t child_pid;

	if ((child_pid = fork()) == 0)
	{
		if(execvp(cmd_arr[0], cmd_arr) == -1) 
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
