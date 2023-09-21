#include "shell.h"

/**
 * input_buffer - Reads and buffers chained commands from standard input
 * @info: Parameter struct
 * @buf: Address of the buffer
 * @len: Address of the length variable
 *
 * Return: Number of bytes read
 */
ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t buffer_length = 0;

/*If nothing left in the buffer, fill it*/
	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
/*Use getline if available, otherwise use _getline*/
#if USE_GETLINE
		bytes_read = getline(buf, &buffer_length, stdin);
#else
		bytes_read = _getline(info, buf, &buffer_length);
#endif
		if (bytes_read > 0)
		{
/*Remove trailing newline if it exists*/
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
/*Check if this is a command chain*/
			if (_strchr(*buf, ';'))
			{
				*len = bytes_read;
				info->cmd_buf = buf;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - Gets a line from input buffer, excluding the newline character
 * @info: Parameter struct
 *
 * Return: Number of bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *command_chain_buffer; /* The ';' command chain buffer*/
	static size_t current_position, next_position, buffer_length;
	ssize_t bytes_read = 0;
	char **current_command_ptr = &(info->arg);
	char *current_command;

	_putchar(BUF_FLUSH);

	bytes_read = input_buffer(info, &command_chain_buffer, &buffer_length);
	if (bytes_read == -1)
		return (-1); /* EOF*/
	if (buffer_length)
	{
		next_position = current_position;
		current_command = command_chain_buffer + current_position;
		checkChain(info, command_chain_buffer, &next_position,
				current_position, buffer_length);

/*Iterate to the semicolon or the end of the buffer*/
		while (next_position < buffer_length)
		{
			if (isChainDelimiter(info, command_chain_buffer, &next_position))
				break;
			next_position++;
		}
		current_position = next_position + 1;
		if (current_position >= buffer_length)
		{
			current_position = buffer_length = 0; /*Reached end of buffer*/
			info->cmd_buf_type = CMD_NORM;
		}
		*current_command_ptr = current_command;
		/*Pass back pointer to current command position*/
		return (_strlen(current_command));
		/*Return length of current command*/
	}
	*current_command_ptr = command_chain_buffer;
	/*Not a chain, pass back buffer from _getline()*/
	return (bytes_read); /*Return length of buffer from _getline()*/

}

/**
 * read_buffer - Reads a buffer
 * @info: Parameter struct
 * @buf: Buffer
 * @i: Size
 *
 * Return: Number of bytes read
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
	{
		return (0);
	}
	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
	{
		*i = bytes_read;
	}
	return (bytes_read);
}

/**
 * _getline - Gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 *
 * Return: Number of bytes read
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Blocks the CTRL-C signal
 * @sig_num: The signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
