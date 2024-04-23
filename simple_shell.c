#include "shell.h"

int main(void)
{
	while(1)
	{
		char *exec_args[128];
		
		if(command_read(exec_args) == -1)
			exit(EXIT_FAILURE);
		
		execute(exec_args);

	}
	return (1);
}
