#include <stdio.h>
#include "../../include/exec_test/minishell.h"
void print_env(t_data *data) 
{
    int i = 0;
    while (data->env[i]) 
    {
        printf("%s\n", data->env[i]);
        i++;
    }
}
