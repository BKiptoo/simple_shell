#include "shell.h"

/**
 * get_history_file - Get the history file path.
 * @info: Pointer to the parameter struct.
 *
 * Return: Allocated string containing the history file
 * path or NULL on failure.
 */
char *get_history_file(info_t *info)
{
	char *home_dir, *history_file_path;

	home_dir = _getenv(info, "HOME=");

	if (!home_dir)
		return (NULL);
	history_file_path = malloc(sizeof(char) * (_strlen(home_dir) +
				_strlen(HIST_FILE) + 2));
	if (!history_file_path)
		return (NULL);
	history_file_path[0] = 0;
	_strcpy(history_file_path, home_dir);
	_strcat(history_file_path, "/");
	_strcat(history_file_path, HIST_FILE);
	return (history_file_path);
}

/**
 * write_history - Write the command history to a file.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		printStringToFileDescriptor(node->str, fd);
		writeCharacterToFileDescriptor('\n', fd);
	}
	writeCharacterToFileDescriptor(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Read command history from a file.
 * @info: Pointer to the parameter struct.
 *
 * Return: Number of history entries on success, 0 on failure.
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Add an entry to the history linked list.
 * @info: Pointer to the parameter struct.
 * @buf: The buffer containing the history entry.
 * @linecount: The history line count (histcount).
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumber the history linked list after changes.
 * @info: Pointer to the parameter struct.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
