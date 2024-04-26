#include "shell.h"


int _printenv(void)
{
	int i;

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

void trim_space(char *s)
{
	int i = 0, j = 0;
	char *copy;

	if (s[0] == ' ')
	{
		copy = strdup(s);

		while (s[i] == ' ')
			i++;

		for (j = 0; s[i] != '\0'; j++)
		{
			copy[j] = s[i];
			i++;
		}

		printf("%s", copy);
		free(copy);
	}
}
	

char *command_path(char *cmd)
{
	char *copy, *token, *path;
	struct stat s;

	path = _getenv(cmd);
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
			return (copy);
		free(copy);
	}

	free(path); 
	return (NULL);
}

void free_args(char *s[])
{
	int i = 0;

	while (s[i] != NULL)
	{
		printf("Ran %d times\n", i + 1);
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
			free_args(cmd_arr);
			perror("execve failed");
			return (-1);
		}
	} else 
		wait(&status);
	
	return (0);
}


int command_read(char *s[])
{
	int count = 0;
	size_t n = 128;
	char *buff = NULL, *token;

	if (getline(&buff, &n, stdin) == -1)
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

	printf("Buffer: %s\n", buff);
	s[count] = NULL;

	return (execute(s));
}
