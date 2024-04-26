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
			free(*exec_args);
			exit(0);
		}

		if (cmd_state == 3)
			continue;

		if (cmd_state == 4)
			break;

		if (istty != 1)
			break;


	}
	return (0);
}
