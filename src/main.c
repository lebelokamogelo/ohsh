#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 1024
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

void ohsh_loop(void);
char *ohsh_read_line(void);
char **ohsh_split_line(char *line);
int ohsh_execute(char **args);

// Builtin shell commands:
int ohsh_help(void);
int ohsh_exit(void);

char *builtin_str[] = {
    "help",
    "exit"};

int ohsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

int main(void)
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
        status = ohsh_execute(args);

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

int ohsh_launch(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
            printf("ohsh: '%s' command not found\n", args[0]);
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        // Error forking
        printf("ohsh: fork failed\n");
    }
    else
    {
        // Parent process
        do
        {
            waitpid(pid, &status, 0);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int ohsh_execute(char **args)
{
    int i;

    if (args[0] == NULL)
    {
        // An empty command was entered.
        return 1;
    }

    for (i = 0; i < ohsh_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            switch (i)
            {
            case 0:
                return ohsh_help();
            case 1:
                return ohsh_exit();
            }
        }
    }

    return ohsh_launch(args);
}

int ohsh_help()
{
    int i;
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < ohsh_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    return 1;
}

int ohsh_exit()
{
    return 0;
}