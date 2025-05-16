#include <stdlib.h>
#include <stdio.h>

#define OHSH_BUFSIZE 1024

void ohsh_loop(void);
char *ohsh_read_line(void);

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

                // Read: Read the command from standard input.
        // Parse: Separate the command string into a program and arguments.
        // Execute: Run the parsed command.
        line = ohsh_read_line();
        args = ohh_split_line(line);
        status = ohsh_execute(args);

        free(line);
        free(args);
    } while (status);
}

char *ohsh_read_line(void)
{
    int bufsize = OHSH_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "ohsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // Read a character
        c = getchar();

        // If EOF, replace it with a null character and return.
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        // If buffer exceeded then reallocate.
        if (position >= bufsize)
        {
            bufsize += OHSH_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "ohsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}