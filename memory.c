#include "shell.h"

/**
 * bfree - Frees a dynamically allocated memory pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 * Return: -2 if an exit request is made, 1 if memory was successfully freed,
 * 0 otherwise.
 */
int bfree(void **ptr)
{
/* Check if 'ptr' is not NULL and if the pointer it references is not NULL */
	if (ptr && *ptr)
	{
/* Free the memory block pointed to by '*ptr' */
		free(*ptr);

/* Set '*ptr' to NULL to avoid accessing the freed memory */
		*ptr = NULL;

/* Return 1 to indicate successful memory deallocation */
		return (1);
	}
	return (0);
}
