#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_len(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - Converts a linked list of strings into an
 * array of strings.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *current = head;
	size_t len = list_len(head), j;
	char **str_array;
	char *str;

	if (!head || !len)
		return (NULL);
	str_array = malloc(sizeof(char *) * (len + 1));
	if (!str_array)
		return (NULL);
	for (len = 0; current; current = current->next, len++)
	{
		str = malloc(_strlen(current->str) + 1);
		if (!str)
		{
			for (j = 0; j < len; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}
		str = _strcpy(str, current->str);
		str_array[len] = str;
	}
	str_array[len] = NULL;
	return (str_array);
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number_to_string(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - Returns the node whose string starts
 * with the specified prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: Matching node or NULL if not found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *str_start = NULL;

	while (node)
	{
		str_start = starts_with(node->str, prefix);
		if (str_start && ((c == -1) || (*str_start == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a specific node in the linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node to find the index of.
 *
 * Return: Index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}