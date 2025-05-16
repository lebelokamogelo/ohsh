#include <stdlib.h>
#include <stdio.h>

void ohsh_loop(void);

int main(int argc, char const *argv[])
{
    // Run command loop
    ohsh_loop();

    return EXIT_SUCCESS;
}

void ohsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("> ");
        line = ohsh_read_line();
        args = ohh_split_line(line);
        status = ohsh_execute(args);

        free(line);
        free(args);
    } while (status);
}