#include "shell.h"

/**
 * main - Entry point for the shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
    info_t shell_info[] = { INFO_INIT }; /* Initialize shell information */
    int file_descriptor = 2; /* File descriptor for error output */
/* Inline assembly to perform some operation on the file descriptor */
    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (file_descriptor)
        : "r" (file_descriptor));

    if (argc == 2)
    {
/* Attempt to open a file specified in the command-line argument */
        file_descriptor = open(argv[1], O_RDONLY);

        if (file_descriptor == -1)
        {
/* Handle different error cases */
            if (errno == EACCES)
                exit(126); /* Permission denied */
            if (errno == ENOENT)
            {
/* Print an error message and exit */
                _eputs(argv[0]);
                _eputs(": 0: Can't open ");
                _eputs(argv[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127); /* File not found */
            }
            return (EXIT_FAILURE); /* Other error, exit with failure code */
        }

/* Update the read file descriptor in shell_info */
        shell_info->readfd = file_descriptor;
    }
/* Populate the environment list */
    populate_environment_list(shell_info);
 /* Read shell history */
    read_history(shell_info);
/* Call the shell function */
    hsh(shell_info, argv);

    return (EXIT_SUCCESS); /* Exit with success code */
}
