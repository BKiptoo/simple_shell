#include "shell.h"

/**
 * clear_info - Initializes the fields of an info_t struct
 * @info: Pointer to the info_t struct to be cleared
 */
void clear_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * set_info - Initializes the fields of an info_t struct based on command arguments
 * @info: Pointer to the info_t struct to be initialized
 * @command_arguments: Argument vector (av) passed to the command
 */
void set_info(info_t *info, char **command_arguments)
{
    int i = 0;

    info->fname = command_arguments[0];
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replaceAlias(info);
        replaceVariables(info);
    }
}

/**
 * free_memoryinfo - Frees the memory allocated for fields of an info_t struct
 * @info: Pointer to the info_t struct
 * @free_all: True if freeing all fields, otherwise only specific fields are freed
 */
void free_memoryinfo(info_t *info, int free_all)
{
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (free_all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            free_list(&(info->env));
        if (info->history)
            free_list(&(info->history));
        if (info->alias)
            free_list(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FLUSH);
    }
}
