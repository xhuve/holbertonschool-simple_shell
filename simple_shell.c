#include "shell.h"

int main(void)
{
	while(1)
	{
		int istty;
		char *exec_args[128];
		
		istty = isatty(STDIN_FILENO);

		if (istty == 1)
			printf("$ ");

		if (command_read(exec_args) != 0)
			exit(EXIT_FAILURE);
		
		if (*exec_args[0] == '\n')
			continue;

		if(execute(exec_args) != 0)
			exit(EXIT_FAILURE);

		if (istty != 1)
			break;

		free(*exec_args);
	}
	return (0);
}
