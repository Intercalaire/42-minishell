#include <stdio.h>
#include "../../include/parsing/minishell.h"
int print_env(t_data *data) 
{
    int i = 0;
    while (data->env[i]) 
    {
        printf("%s\n", data->env[i]);
        i++;
    }
    return (0);
}
