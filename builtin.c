#include "shell.h"

/**
 * exit_shell - Exit the shell
 * @info: A structure containing shell information and arguments.
 *
 * This function is used to exit the shell program. It checks for an exit
 * argument, converts it to an integer, and handles errors if the argument
 * is not a valid integer. It updates the shell's status and error number
 * accordingly and returns a special value (-2) to indicate an exit request.
 *
 * Return: -2 if an exit request is made, otherwise, it sets err_num to -1.
 */
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
/*Check if an exit argument is provided*/
		exit_status = _string_to_int(info->argv[1]);
		if (exit_status == -1)
		{
/*Handle the case where the argument is not a valid integer*/
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (-2);
		}

/*Set the error number to the exit status*/
		info->err_num = exit_status;
		return (-2);
	}

/* No exit argument provided, set the error number to -1*/
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Change the current directory of the shell process
 * @info: A structure containing shell information and arguments.
 *
 * This function changes the current directory of the shell process. It handles
 * different cases, such as changing to the home directory or the previous
 * working directory ("-"). It also updates the "OLDPWD" and "PWD" environment
 * variables accordingly.
 *
 * Return: Always returns 0.
 */
int change_directory(info_t *info)
{
	char *cwd, *new_dir, buffer[1024];
	int chdir_result;
/*Get the current working directory*/
	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: Handle getcwd failure here\n");
	if (!info->argv[1])
	{
/*No argument provided, change to the home directory or root*/
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_result = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_result = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
/*Change to the previous working directory ("-")*/
		if (!_getenv(info, "OLDPWD="))
		{
/*Handle the case where "OLDPWD" is not set*/
			_puts(cwd);
			_putchar('\n');
			return (1);
		}

/*Change to the old working directory and print it*/
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_result = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
	{
/*Change to the specified directory*/
		chdir_result = chdir(info->argv[1]);
	}

	if (chdir_result == -1)
	{
/*Handle the case where chdir fails*/
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
/*Update "OLDPWD" and "PWD" environment variables*/
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

return (0);
}

/**
 * display_help - Display a help message (not yet implemented)
 * @info: A structure containing shell information and arguments.
 *
 * This function is a placeholder for displaying help information. It prints
 * a message indicating that the help function is not yet implemented.
 *
 * Return: Always returns 0.
 */
int display_help(info_t *info)
{
	char **arguments = info->argv;

/*Print a message indicating that help is not yet implemented*/
	_puts("Help function is not yet implemented.\n");
/*Temporarily suppress unused variable warning*/
	if (0)
		_puts(*arguments);

	return (0);
}

