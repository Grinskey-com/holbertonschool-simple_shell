# Holberton Integration Project: Simple Shell

This integration project has tasked us to create a simple UNIX command interpreter using the knowledge that we have obtained in C. This project's purpose was to help us understand what goes on under the hood of how a shell works, like 'sh' - reading input, resolving commands against 'PATH' and running them as child processes.

## Description

Our shell implements the core read -> parse -> execute loop of a shell:

1. If running interactively - print a prommpt
2. Read a line of input
3. Split it into a command and its arguments
4. Check for whether the command is a builtin - otherwise resolve against 'PATH' or if it contains a '/', use it directly.
5. Fork a child process -> execve the resolved executable and wait for it to finish.
6. Repeat - until end of file or exit command.

## Compilation

The compilation flags as per task requirements that have been used to test and ccompile our shell is:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage

### Interactive mode

```sh
$ ./hsh
$ /bin/ls
hsh  main.c  execute.c  find_path.c  input.c  token.c  builtins.c  shell.h
$ ls
hsh  main.c  execute.c  find_path.c  input.c  token.c  builtins.c  shell.h
$ exit
```

Prompt (`$ `) is only printed when stdin is a terminal - so
piped input runs silently.

### Non - Interactive mode

```sh
$ echo "/bin/ls" | ./hsh
hsh  main.c  execute.c  find_path.c  input.c  token.c  builtins.c  shell.h
```

### End of file

Pressing CTRL + D during interactive mode exits the shell cleanly - printing
a newline first, similar as to how normal 'sh' does it.

## Builtins

| Command | Behavior |
|---|---|
| `exit` | Exits the shell immediately with success status. |
| `env`  | Prints the current environment, one `KEY=value` pair per line.

## Command resolution

- A command containing a `/` (e.g. `./hsh`, `/bin/ls`) is checked directly
for executability.
- A bare command name (e.g. `ls`) is searched for across each directory
listed in the `PATH` environment variable, in order.
- If no executable match is found, the shell prints `Command not found` and
returns to the prompt without forking.

## File structure
main.c : Entry point - owns the main prompt/read/execute loop

input.c : Reads a line of input and trims trailing whitespace/newline

token.c : Splits a line into a 'NULL' terminated array of argument tokens

execute.c : Dispatches builtins, resolves command path, handles fork and execve.

find_path.c : Resolves a command name to an executable path via 'PATH' or direct access

builtins.c : Implements env / _getenv, and the exit builtin (builtin_exit) with numeric-argument validation (is_shell_number, shell_atol); handle_builtin dispatches argv[0] to the matching built in.

shell.h : Shell header - includes environt decleration and function prototypes.

## Known limitations

- Additional built ins like cd, setenv, unsetenv, etc.
- Command separators/operators like ';', '&&', etc.
- Comments, quoting and I/O redirection

## Authors
Ezekiel Grimsley
Jeiel Roco
- 2026
