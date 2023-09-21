#include "shell.h"

/**
 *strtow - splits a string into words using multiple delimiters
 * @input_str: the input string to split
 * @delimiters: a string containing delimiters
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *input_str, char *delimiters)
{
	int i, j, k, m, num_words = 0;
	char **result;

	/* Check for NULL or empty input string */
	if (input_str == NULL || input_str[0] == '\0')
		return (NULL);

	/* If delimiters is NULL, use a space as the default delimiter */
	if (!delimiters)
		delimiters = " ";

	/* Count the number of words in the input string */
	for (i = 0; input_str[i] != '\0'; i++)
		if (!isDelimiter(input_str[i], delimiters) &&
		    (isDelimiter(input_str[i + 1], delimiters) || !input_str[i + 1]))
			num_words++;

	/* If no words found, return NULL */
	if (num_words == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		/* Skip leading delimiters */
		while (isDelimiter(input_str[i], delimiters))
			i++;

		k = 0;
		/* Copy characters until the next delimiter or end of string */
		while (!isDelimiter(input_str[i + k], delimiters) && input_str[i + k])
			k++;

		/* Allocate memory for the current word */
		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j])
		{
			/* Free previously allocated memory on failure */
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}

		/* Copy characters into the current word */
		for (m = 0; m < k; m++)
			result[j][m] = input_str[i++];
		result[j][m] = '\0';
	}

	/* Null-terminate the result array */
	result[j] = NULL;

	return (result);
}

/**
 * split_string_single_delimiter - splits a string into words
 * using a single delimiter
 * @input_str: the input string to split
 * @delimiter: the delimiter character
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string_single_delimiter(char *input_str, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **result;

	/* Check for NULL or empty input string */
	if (input_str == NULL || input_str[0] == '\0')
		return (NULL);

	/* Count the number of words in the input string */
	for (i = 0; input_str[i] != '\0'; i++)
		if ((input_str[i] != delimiter && input_str[i + 1] == delimiter) ||
		    (input_str[i] != delimiter && !input_str[i + 1]) ||
		    input_str[i + 1] == delimiter)
			num_words++;

	/* If no words found, return NULL */
	if (num_words == 0)
		return (NULL);

	/* Allocate memory for the array of strings */
	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		/* Skip leading delimiters */
		while (input_str[i] == delimiter && input_str[i] != delimiter)
			i++;

		k = 0;
		/* Copy characters until the next delimiter or end of string */
		while (input_str[i + k] != delimiter &&
				input_str[i + k] && input_str[i + k] != delimiter)
			k++;

		/* Allocate memory for the current word */
		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j])
		{
			/* Free previously allocated memory on failure */
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}

		/* Copy characters into the current word */
		for (m = 0; m < k; m++)
			result[j][m] = input_str[i++];
		result[j][m] = '\0';
	}

	/* Null-terminate the result array */
	result[j] = NULL;

	return (result);
}
