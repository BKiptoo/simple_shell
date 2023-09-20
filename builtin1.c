#include "shell.h"

/**
 * displayCommandHistory - Displays the command history list, one command per line,
 *              with line numbers starting at 0.
 * @info: A structure containing potential arguments and history information.
 *
 * Return: Always returns 0.
 */
int displayCommandHistory(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unsetAlias - Unsets an alias by removing it from the alias list.
 * @info: The parameter struct containing alias information.
 * @str: The string representing the alias to unset.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int unsetAlias(info_t *info, char *str)
{
    char *equalSignPos, savedChar;
    int ret;

    equalSignPos = _strchr(str, '=');
    if (!equalSignPos)
        return (1);

    savedChar = *equalSignPos;
    *equalSignPos = '\0';

/*Delete the alias from the list and restore the '=' character.*/ 
    ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *equalSignPos = savedChar;

    return (ret);
}

/**
 * setAlias - Sets an alias by adding it to the alias list.
 * @info: The parameter struct containing alias information.
 * @str: The string representing the alias to set.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int setAlias(info_t *info, char *str)
{
    char *equalSignPos;

    equalSignPos = _strchr(str, '=');
    if (!equalSignPos)
        return (1);

    if (!*++equalSignPos)
        return (unsetAlias(info, str));

    unsetAlias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printAlias - Prints an alias string.
 * @node: The alias node containing the alias string.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int printAlias(list_t *node)
{
    char *equalSignPos = NULL, *aliasName = NULL;

    if (node)
    {
        equalSignPos = _strchr(node->str, '=');
/*Print the alias name and value.*/ 
        for (aliasName = node->str; aliasName <= equalSignPos; aliasName++)
            _putchar(*aliasName);

        _putchar('\'');
        _puts(equalSignPos + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * aliasCommand- Mimics the 'alias' built-in command (man alias).
 * @info: The structure containing potential arguments and alias information.
 *
 * Return: Always returns 0.
 */
int aliasCommand(info_t *info)
{
    int i = 0;
    char *equalSignPos = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
/*If no arguments provided, print all aliases.*/ 
        node = info->alias;
        while (node)
        {
            printAlias(node);
            node = node->next;
        }
        return (0);
    }

/*Loop through arguments and either set new aliases or print existing ones.*/ 
    for (i = 1; info->argv[i]; i++)
    {
        equalSignPos = _strchr(info->argv[i], '=');

        if (equalSignPos)
            setAlias(info, info->argv[i]);
        else
            printAlias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
