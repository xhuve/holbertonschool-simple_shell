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

int execute(char *cmd_arr[])
{
	int status;
	pid_t child_pid;

	if ((child_pid = fork()) == 0)
	{
		if(execve(cmd_arr[0], cmd_arr, environ) == -1) 
		{
			
			perror("execve failed");
			return (-1);
		}
	} else 
	{
		wait(&status);
	}
	
	return (0);
}


int command_read(char *s[])
{
	int count = 0, value;
	size_t n = 128;
	char *buff = NULL, *token;

	value = getline(&buff, &n, stdin);

	if (value == -1)
	{
		perror("Error reading input");
		free(buff);
		return (-1);
	}

	if (strcmp(buff, "\n") == 0)
	{
		free(buff);
		return (3);
	}

	if (strcmp(buff, "exit\n") == 0)
	{
		free(buff);
		return (4);
	}

	token = strtok(buff, "\t\n");

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

	return (execute(s));
}
