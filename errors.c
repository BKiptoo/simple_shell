#include "shell.h"

/**
 * _eputs - Prints an input string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;

/* Iterate through the string and print each character to stderr.*/
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and sets errno appropriately.
 */
int _eputchar(char c)
{
	static int bufferIndex;
	static char buffer[WRITE_BUF_SIZE];

/*If the character is a flush signal write the buffer to stderr.*/
	if (c == BUF_FLUSH || bufferIndex >= WRITE_BUF_SIZE)
	{
		write(2, buffer, bufferIndex);
		bufferIndex = 0;
	}

/* If the character is not a flush signal, add it to the buffer.*/
	if (c != BUF_FLUSH)
		buffer[bufferIndex++] = c;

	return (1);
}

/**
 * writeCharacterToFileDescriptor - Writes the character
 * c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and sets errno appropriately.
 */
int writeCharacterToFileDescriptor(char c, int fd)
{
	static int bufferIndex;
	static char buffer[WRITE_BUF_SIZE];

/* is char is a flush signal write the buffer to the specified fd.*/
	if (c == BUF_FLUSH || bufferIndex >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, bufferIndex);
		bufferIndex = 0;
	}

/*If the character is not a flush signal, add it to the buffer.*/
	if (c != BUF_FLUSH)
		buffer[bufferIndex++] = c;

	return (1);
}

/**
 * printStringToFileDescriptor - Prints an input string
 * to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int printStringToFileDescriptor(char *str, int fd)
{
	int charCount = 0;

	if (!str)
		return (0);

/*Iterate through the string write each character to the specified fd.*/
	while (*str)
	{
		charCount += writeCharacterToFileDescriptor(*str++, fd);
	}
	return (charCount);
}