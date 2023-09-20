#include "shell.h"

/**
 * isChainDelimiter - Check if the current character in the buffer is a chain delimiter
 * @info: The parameter struct
 * @buffer: The character buffer
 * @position: Address of the current position in the buffer
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int isChainDelimiter(info_t *info, char *buffer, size_t *position)
{
    size_t currentPos = *position;

    if (buffer[currentPos] == '|' && buffer[currentPos + 1] == '|')
    {
        buffer[currentPos] = 0; /* Replace '||' with null terminator */
        currentPos++;
        info->cmd_buf_type = CMD_OR; /* Set command buffer type to CMD_OR */
    }
    else if (buffer[currentPos] == '&' && buffer[currentPos + 1] == '&')
    {
        buffer[currentPos] = 0; /* Replace '&&' with null terminator */
        currentPos++;
        info->cmd_buf_type = CMD_AND; /* Set command buffer type to CMD_AND */
    }
    else if (buffer[currentPos] == ';') /* Found end of this command */
    {
        buffer[currentPos] = 0; /* Replace semicolon with null terminator */
        info->cmd_buf_type = CMD_CHAIN; /* Set command buffer type to CMD_CHAIN */
    }
    else
    {
        return (0); /* Not a chain delimiter */
    }
    *position = currentPos;
    return (1); /* It's a chain delimiter */
}

/**
 * checkChain - Check if we should continue chaining based on the last status
 * @info: The parameter struct
 * @buffer: The character buffer
 * @position: Address of the current position in the buffer
 * @startPos: Starting position in the buffer
 * @bufferLength: Length of the buffer
 *
 * Return: Void
 */
void checkChain(info_t *info, char *buffer, size_t *position, size_t startPos, size_t bufferLength)
{
    size_t currentPos = *position;

    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buffer[startPos] = 0; /* Replace the command with null terminator */
            currentPos = bufferLength;
        }
    }
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buffer[startPos] = 0; /* Replace the command with null terminator */
            currentPos = bufferLength;
        }
    }

    *position = currentPos;
}

/**
 * replaceAlias - Replace aliases in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0); /* Alias not found */

        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0); /* Invalid alias format */

        p = _strdup(p + 1);
        if (!p)
            return (0); /* Memory allocation error */

        info->argv[0] = p;
    }
    return (1); /* Aliases replaced successfully */
}

/**
 * replaceVariables - Replace variables in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVariables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replaceString(&(info->argv[i]), _strdup(convert_number_to_string(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replaceString(&(info->argv[i]), _strdup(convert_number_to_string(getpid(), 10, 0)));
            continue;
        }
        node = node_starts_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replaceString(&(info->argv[i]),_strdup((_strchr(node->str, '=') + 1)));
            continue;
        }
        replaceString(&(info->argv[i]), _strdup(""));
    }
    return (0); /* Variables replaced */
}

/**
 * replaceString - Replace a string
 * @oldString: Address of the old string
 * @newString: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceString(char **oldString, char *newString)
{
    free(*oldString);
    *oldString = newString;
    return (1); /* String replaced */
}
