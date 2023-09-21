#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @dest: Pointer to the memory area to be filled.
 * @byte: The byte value to fill @dest with.
 * @n: The number of bytes to be filled.
 * Return: A pointer to the memory area @dest.
 */
char *_memset(char *dest, char byte, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)

		dest[index] = byte;
	return (dest);
}

/**
 * ffree- Frees memory allocated for an array of strings.
 * @str_array: The array of strings to be freed.
 */
void ffree(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temp);
}

/**
 * _realloc - Reallocates memory for a block of data.
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: Size (in bytes) of the previous memory block.
 * @new_size: Size (in bytes) of the new memory block.
 * Return: A pointer to the new memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

/*Copy the data from the old block to the new block*/
	old_size = (old_size < new_size) ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];

/*Free the old memory block*/
	free(ptr);
	return (new_ptr);
}