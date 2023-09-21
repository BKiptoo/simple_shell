#include "shell.h"

/**
 * get_environ - Retrieves the copy of the environment
 * variables as an array of strings.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: An array of strings representing the environment variables.
 */
char **get_environ(info_t *info)
{
/*check if the environment hasn't been initialized or if it has changed.*/
	if (!info->environ || info->env_changed)
	{
/* Convert the linked list of environment variables to an array of strings.*/
	    info->environ = list_to_strings(info->env);
	    info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * unset_environment_variable - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * @var: The name of the environment variable to be removed.H
 * Return: 1 if the variable was deleted, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *equals_position;
/*Check if the environment or the variable name is invalid.*/
	if (!node || !var)
		return (0);

	while (node)
	{
/*Check if the current environment variable starts with the specified name.*/
		equals_position = starts_with(node->str, var);
		if (equals_position && *equals_position == '=')
		{
/*Delete the environment variable from the linked list.*/
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
/**
 * _setenv - Initializes a new environment variable or
 * modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * @var: The name of the environment variable.
 * @value: The value to be set for the environment variable.
 * Return: Always returns 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *env_variable = NULL;
	list_t *node;
	char *equals_position;

/*Check if the variable name or value is invalid.*/
	if (!var || !value)
		return (0);

/* Allocate memory for the environment variable string.*/
	env_variable = malloc(_strlen(var) + _strlen(value) + 2);
	if (!env_variable)
		return (1);

/* Construct the environment variable string in the format "name=value".*/
	_strcpy(env_variable, var);
	_strcat(env_variable, "=");
	_strcat(env_variable, value);

	node = info->env;
	while (node)
	{
/*Check if the current environment variable starts with the specified name.*/
		equals_position = starts_with(node->str, var);
		if (equals_position && *equals_position == '=')
		{
/*Free the old environment variable string and replace it with the new one.*/
			free(node->str);
			node->str = env_variable;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

/*Add the new environment variable to the end of the linked list.*/
	add_node_end(&(info->env), env_variable, 0);
	free(env_variable);
	info->env_changed = 1;
	return (0);
}