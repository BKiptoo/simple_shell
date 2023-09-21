#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: Pointer to the info struct.
 * @file_path: Path to the file to be checked.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *file_path)
{
	struct stat file_stat;

	(void)info;

/* Check if the file path is NULL or if stat fails. */
	if (!file_path || stat(file_path, &file_stat) != 0)
		return (0);

/* Check if the file is a regular file (executable). */
	if (S_ISREG(file_stat.st_mode))
	{
		return (1);
	}
	return (0);
}

/**
 * extract_substring - Extracts a substring from the given string.
 * @input_string: The input string.
 * @start_index: Starting index of the substring.
 * @end_index: Ending index of the substring.
 *
 * Return: Pointer to a new buffer containing the extracted substring.
 */
char *extract_substring(char *input_string, int start_index, int end_index)
{
	static char buffer[1024];
	int i = 0, buffer_index = 0;

	for (buffer_index = 0, i = start_index; i < end_index; i++)
	{
		if (input_string[i] != ':')
			buffer[buffer_index++] = input_string[i];
	}
	buffer[buffer_index] = '\0';
	return (buffer);
}

/**
 * find_path - Finds the full path of a command in the PATH string.
 * @info: Pointer to the info struct.
 * @path_string: The PATH string containing a list of directories.
 * @command_name: The name of the command to find.
 *
 * Return: Full path of the command if found, or NULL if not found.
 */
char *find_path(info_t *info, char *path_string, char *command_name)
{
	int path_index = 0;
	int current_position = 0;
	char *full_path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command_name) > 2) && starts_with(command_name, "./"))
	{
		if (is_cmd(info, command_name))
			return (command_name);
	}
	while (1)
	{
		if (!path_string[path_index] || path_string[path_index] == ':')
		{
			full_path = extract_substring(path_string, current_position, path_index);
			if (!*full_path)
				_strcat(full_path, command_name);
			else
			{
				_strcat(full_path, "/");
				_strcat(full_path, command_name);
			}
			if (is_cmd(info, full_path))
				return (full_path);
			if (!path_string[path_index])
				break;
			current_position = path_index + 1;
		}
		path_index++;
	}
	return (NULL);
}

