#include "shell.h"

int main(void)
{
	while(1)
	{
		int arg_len;
		char *exec_args[128];
		
		if(command_read(exec_args) == -1)
			exit(EXIT_FAILURE);
		


	}
}
