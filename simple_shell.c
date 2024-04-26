#include "shell.h"

int main(void)
{
	int istty, cmd_state;
	char *exec_args[128];

	while(1)
	{		
		istty = isatty(STDIN_FILENO);

		if (istty == 1)
			printf("$ ");

		cmd_state = command_read(exec_args);
		
		if (cmd_state == -1)
		{
			exit(0);
		}

		if (cmd_state == 3)
			continue;

		if (cmd_state == 4)
		{
			free_args(exec_args);
			exit(EXIT_SUCCESS);
		}


		if (istty != 1)
			break;

		free(*exec_args);
	}
	return (0);
}
