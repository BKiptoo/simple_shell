#include "shell.h"

/**
 * hsh - Main loop of the shell
 * @info: Pointer to the shell information struct
 * @av: Address of the pointer to free.
 * Return:- 0 on success
 *   - 1 on error
 *   - Error code otherwise
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (isInteractiveMode(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin_command(info);
			if (builtin_ret == -1)
				find_command(info);
		}
		else if (isInteractiveMode(info))
			_putchar('\n');
		free_memoryinfo(info, 0);
	}
	write_history(info);
	free_memoryinfo(info, 1);
	if (!isInteractiveMode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}



/**
 * find_builtin_command - Find a built-in command in the shell
 * @info: Pointer to the shell information struct
 *
 * Return: -1 if the built-in command is not found
 *   - 0 if the built-in command is executed successfully
 *   - 1 if the built-in command is found but not successful
 *   - -2 if the built-in command signals an exit
 */
int find_builtin_command(info_t *info)
{
	int i, builtin_return_code = -1;
	builtin_table built_in_commands[] = {
		{"exit", exit_shell},
		{"env", _myenvironment},
		{"help", display_help},
		{"history", displayCommandHistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", change_directory},
		{"alias", aliasCommand},
		{NULL, NULL}
	};

	for (i = 0; built_in_commands[i].type; i++)
	{
		if (_strcmp(info->argv[0], built_in_commands[i].type) == 0)
		{
			info->line_count++;
			builtin_return_code = built_in_commands[i].func(info);
			break;
		}
	}

	return (builtin_return_code);
}

/**
 * find_command - Find and execute an external command
 * @info: Pointer to the shell information struct
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isDelimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((isInteractiveMode(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - Fork a new process and execute an
 * external command
 * @info: Pointer to the shell information struct
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_memoryinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
