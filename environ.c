#include "shell.h"

/**
 * print_environment - Prints the current environment variables
 * @info: Pointer to a structure containing potential arguments and environment data.
 *
 * This function prints the list of environment variables.
 */
int _myenvironment(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * _getenv - Gets the value of an environment variable
 * @info: Pointer to a structure containing potential arguments and environment data.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: The value of the specified environment variable, or NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *value;

    while (node)
    {
        value = starts_with(node->str, name);
        if (value && *value)
            return (value);
        node = node->next;
    }
    return (NULL);
}

/**
 * set_environment_variable - Initialize a new environment variable or modify an existing one
 * @info: Pointer to a structure containing potential arguments and environment data.
 *
 * This function sets or modifies an environment variable.
 *
 * Return: 0 on success, or 1 on failure.
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Pointer to a structure containing potential arguments and environment data.
 *
 * This function removes one or more environment variables.
 *
 * Return: 0 on success, or 1 on failure.
 */
int _myunsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("There are too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * populate_environment_list - Populates the environment linked list with current environment variables
 * @info: Pointer to a structure containing potential arguments and environment data.
 *
 * This function initializes the environment linked list with the current environment variables.
 *
 * Return: 0 on success, or 1 on failure.
 */
int populate_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}
