#include "shell.h"

int main(void)
{
	while(1)
	{
		char *exec_args[128];
		
		if(command_read(exec_args) == -1)
			exit(EXIT_FAILURE);
		
		if(execute(exec_args) == -1)
		{
			perror("execute error");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
