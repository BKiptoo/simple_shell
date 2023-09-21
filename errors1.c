#include "shell.h"

/**
 * _string_to_int - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: The converted integer on success, -1 on error.
 */
int _string_to_int(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;/*Skip leading plus sign, if present
*/
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1); /*Integer overflow error*/
		}
		else
			return (-1); /*Non-numeric character error*/
	}
	return (result);
}

/**
 * print_error - Prints an error message to standard error.
 * @info: Pointer to the parameter and return info struct.
 * @error_str: String containing the specified error type.
 */
void print_error(info_t *info, char *error_str)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_str);
}
/**
 * print_decimal - Prints a decimal (integer) number to a file descriptor.
 * @num: The integer to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int num, int fd)
{
	int (*output_char)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		output_char = _eputchar;

	if (num < 0)
	{
		absolute_value = -num;
		output_char('-');
		count++;
	}
	else
		absolute_value = num;

	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			output_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	output_char('0' + current);
	count++;
	return (count);
}

/**
 * convert_number_to_string - Converts a number to a string representation.
 * @num: The number to convert.
 * @base: The base of the number (e.g., 10 for decimal).
 * @flags: Argument flags.
 *
 * Return: A string representation of the number.
 */
char *convert_number_to_string(long int num, int base, int flags)
{
	static char *digit_array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	digit_array = flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = digit_array[n % base];
		n /= base;
	}
	while (n != 0)
		if (sign)
			*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Replaces the first instance of '#'
 * with '\0' in the string.
 * @buf: Address of the string to modify.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}