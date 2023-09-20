#include "shell.h"

/**
 * isInteractiveMode - Checks if the shell is running in interactive mode
 * @info: Pointer to a struct containing shell information
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int isInteractiveMode(info_t *info)
/*Check if standard input is associated with a terminal and if readfd <= 2*/
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


/**
 * isDelimiter - Checks if a character is a delimiter
 * @c: The character to check
 * @delimiters: String containing delimiters
 *
 * Return: 1 if 'c' is a delimiter, 0 otherwise
 */
int isDelimiter(char c, char *delimiters)
{
/*Iterate through the delimiter string*/
while (*delimiters) 
{
    if (*delimiters == c)
    {
        return (1); /*Character 'c' is a delimiter*/
    }
        delimiters++;
}
return (0); /*Character 'c' is not a delimiter*/
}

/**
 * isAlphabetic - Checks if a character is alphabetic
 * @c: The character to check
 *
 * Return: 1 if 'c' is an alphabetic character, 0 otherwise
 */
int isAlphabetic(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return (1); /*Character 'c' is an alphabetic character*/
    } else 
    {
        return (0); /* Character 'c' is not an alphabetic character*/
    }
}

/**
 * stringToInteger - Converts a string to an integer
 * @s: The string to be converted
 *
 * Return: The integer value if valid, 0 if no valid integer found
 */
int stringToInteger(char *s)
{
int i, sign = 1, flag = 0, result = 0;
/* Initialize 'result' and 'flag' to 0, 'sign' to 1, and 'output' to 0 */

for (i = 0; s[i] != '\0' && flag != 2; i++)
{
    if (s[i] == '-')
    {
        sign *= -1; /* Handle negative sign */
    }

    if (s[i] >= '0' && s[i] <= '9')
    {
        flag = 1; /*Indicate that digits have been encountered*/ 
        result *= 10; /*Multiply the current result by 10*/ 
        result += (s[i] - '0'); /*Add the numeric value of the character*/ 
    }
    else if (flag == 1)
    {
            flag = 2; /*Stop processing after encountering non-digit characters*/ 
    }
}
    if (sign == -1)
    {
        return (-result); /*Apply negative sign if necessary*/ 
    }
    else
    {
        return (result); /* Return the result as a positive integer*/ 
    }
}
