#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 1024
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

void ohsh_loop(void);
char *ohsh_read_line(void);
char **ohsh_split_line(char *line);

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
        args = ohsh_split_line(line);
        // status = ohsh_execute(args);

        free(line);
        free(args);
    } while (status);
}

char *ohsh_read_line(void)
{
    int bufsize = BUFSIZE;
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
            bufsize += BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "ohsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **ohsh_split_line(char *line)
{
    int bufsize = TOKEN_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "ohsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIM);

    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "ohsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}