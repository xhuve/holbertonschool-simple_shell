#include "shell.h"

int main(void)
{
	while(1)
	{
		char *exec_args[128];
		
		if(command_read(exec_args) != 0)
			exit(EXIT_FAILURE);
		
		if (exec_args[0] == NULL || strspn(exec_args[0], " ") == strlen(exec_args[0]))
			continue;

		if(execute(exec_args) != 0)
			exit(EXIT_FAILURE);

	}
	return (0);
}
