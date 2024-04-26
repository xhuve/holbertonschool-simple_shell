# Simple Shell in C

This is a simple implementation of a Unix shell in C programming language. The shell supports executing external commands, handling command-line arguments, and implementing the `env` and `exit` built-in commands.

## Features

- Execute external commands with command-line arguments
- Implement the `env` built-in command to print the environment variables
- Implement the `exit` built-in command to terminate the shell
- Support interactive mode (reading commands from the terminal) and non-interactive mode (reading commands from a file or pipe)

## Usage

To compile and run the shell, follow these steps:

1. Compile the source code using a C compiler:
```
gcc -o shell shell.c
```

2. Run the compiled executable:
```
./shell
```

3. In the shell prompt (`$`), enter commands to execute. For example:
```
$ ls -l
$ env
$ exit
```
## Code Structure

The code is structured into several functions:

- `_printenv()`: Prints the environment variables to the standard output.
- `execute(char *cmd_arr[])`: Forks a child process and executes the command using `execvp`.
- `command_tok(char *line)`: Tokenizes the input command line and executes the command.
- `main()`: The main loop that reads input commands, handles built-in commands (`env` and `exit`), and passes external commands to `command_tok`.

## Built-in Commands

### env

The `env` command prints the environment variables to the standard output. It is implemented by the `_printenv()` function.

### exit

The `exit` command terminates the shell process. It is handled by checking if the input line matches "exit\n" in the `main()` function.

## Limitations

This simple shell implementation has several limitations:

- It does not handle input/output redirection or piping.
- It does not support complex command syntax (e.g., parentheses, logical operators).
- It does not implement any advanced features like aliases, history, or tab completion.
- Error handling and memory management could be improved.

## Further Improvements

Here are some potential improvements that could be made to this shell implementation:

- Implement input/output redirection and piping.
- Support more built-in commands (e.g., `cd`, `pwd`, `echo`).
- Improve error handling and error messages.
- Implement advanced features like command history, tab completion, and aliases.
- Optimize memory management and resource cleanup.
- Add support for environment variable manipulation (e.g., `export`, `unset`).
- Enhance the handling of signals (e.g., `Ctrl+C`, `Ctrl+Z`).

Please note that this implementation is intended for educational purposes and should not be used in production environments without further enhancements and thorough testing.
