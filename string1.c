#include "shell.h"

/**
 * _strcpy - Copies a source string into a destination string.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
    int index = 0;

/* Check for special cases */
    if (dest == src || src == NULL)
        return (dest);

/* Copy characters from source to destination */
    while (src[index])
    {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0'; /* Null-terminate the destination string */
    return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
    int length = 0;
    char *duplicate;

/* Check for NULL input */
    if (str == NULL)
        return (NULL);

/* Calculate the length of the input string */
    while (*str++)
        length++;
/* Allocate memory for the duplicate string */
    duplicate = malloc(sizeof(char) * (length + 1));
    if (!duplicate)
        return (NULL);
/* Copy characters from input to duplicate */
    for (length++; length--;)
        duplicate[length] = *--str;

    return (duplicate);
}

/**
 * _puts - Prints a null-terminated string to stdout.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
    int index = 0;

/* Check for NULL input */
    if (!str)
        return;

/* Print characters in the string */
    while (str[index] != '\0')
    {
        _putchar(str[index]);
        index++;
    }
}

/**
 * _putchar - Writes a character to stdout.
 * @c: The character to print.
 *
 * Return: On success, returns 1.
 * On error, returns -1 and sets errno appropriately.
 */
int _putchar(char c)
{
    static int buffer_index;
    static char buffer[WRITE_BUF_SIZE];
/* Check if the buffer needs to be flushed or is full */
    if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
    {
        write(1, buffer, buffer_index);
        buffer_index = 0;
    }

/* Add the character to the buffer, unless it's a flush indicator */
    if (c != BUF_FLUSH)
        buffer[buffer_index++] = c;

    return (1);
}
