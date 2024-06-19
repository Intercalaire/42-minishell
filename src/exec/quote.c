#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *parse_command(t_data *data, char *command) {
    char *token;
    int i = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    char *start_of_var = NULL;

    while (command[i] != '\0') {
        if (command[i] == '\'') {
            in_single_quote = !in_single_quote;
        } else if (command[i] == '\"') {
            in_double_quote = !in_double_quote;
        } else if (command[i] == ' ') {
            if (!in_single_quote && !in_double_quote) {
                command[i] = '\0';
            }
        } else if (command[i] == '$') {
            if (in_double_quote && !in_single_quote) {
                start_of_var = &command[i];
            }
        } else {
            if (start_of_var) {
                if (command[i] == ' ' || command[i] == '\'' || command[i] == '\"') {
                    char old_char = command[i];
                    command[i] = '\0';
                    char *value = my_getenv(data, start_of_var + 1);
                    if (value) {
                        printf("%s", value);
                    }
                    command[i] = old_char;
                    start_of_var = NULL;
                }
            }
        }
        i++;
    }

    token = ft_strtok(command, "\0");
    while (token != NULL) {
        printf("'%s'\n", token);
        token = ft_strtok(NULL, "\0");
    }
}

char *my_getenv(t_data *data, char *var) 
{
    int i
    char *value;

    i = search_env(data, var);
    value = ft_strdup(data->env[i] + ft_strlen(var) + 1);
    return (value);
}


