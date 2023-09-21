#include "shell.h"

/**
 * _strncpy - Copies a string with a maximum length.
 * @destination: The destination string where the copy will be placed.
 * @source: The source string to be copied from.
 * @max_length: The maximum number of characters to copy.
 * Return: -2 if an exit request is made
 * This function copies up to 'max_length' characters
 * from 'source' to 'destination'.
 * If 'max_length' is greater than the length of 'source',
 * it copies the entire string.
 * Returns a pointer to 'destination'.
 */
char *_strncpy(char *destination, char *source, int max_length)
{
	int source_index = 0, destination_index = 0;
	char *original_destination = destination;

	while (source[source_index] != '\0' && source_index < max_length - 1)
	{
		destination[destination_index] = source[source_index];
		source_index++;
		destination_index++;
	}
	if (source_index < max_length)
	{
		while (destination_index < max_length)
		{
			destination[destination_index] = '\0';
			destination_index++;
		}
	}
	return (original_destination);
}

/**
 * _strncat - Concatenates two strings with a maximum length.
 * @destination: The first string.
 * @source: The second string to be concatenated.
 * @max_length: The maximum number of bytes to use.
 * Return: -2 if an exit request is made
 * This function concatenates up to 'max_length'
 * bytes from 'source' to the end of 'destination'.
 * If 'max_length' is greater than the available space in
 * 'destination', it appends as much as possible.
 * Returns a pointer to 'destination'.
 */
char *_strncat(char *destination, char *source, int max_length)
{
	int destination_index = 0, source_index = 0;
	char *original_destination = destination;

	while (destination[destination_index] != '\0')
		destination_index++;

	while (source[source_index] != '\0' && source_index < max_length)
	{
		destination[destination_index] = source[source_index];
		destination_index++;
		source_index++;
	}
	if (source_index < max_length)
		destination[destination_index] = '\0';
	return (original_destination);
}

/**
 * _strchr -Locates a character in a string.
 * @string: The string to be searched.
 * @character: The character to search for.
 *  Return: -2 if an exit request is made, otherwise
 * Returns pointer This function searches for 'character' in 'string'.
 * If found, it returns a pointer to the first occurrence of
 * 'character' in 'string'.
 * If not found, it returns NULL.
 */
char *_strchr(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');
	return (NULL);
}
