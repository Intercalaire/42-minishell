#include "../../include/parsing/minishell.h"

int exec(t_data *data, char *cmd, char **arg, char *str)
{
    int i;


    i = 0;
    if (!ft_strncmp(cmd, "echo", 4))
        data->exit_status = echo(data, arg);
    else if (!ft_strncmp(cmd, "pwd", 3))
        data->exit_status = pwd();
    else if (!ft_strncmp(cmd, "env", 3))
        data->exit_status = print_env(data);
    else if (!ft_strncmp(cmd, "export", 6))
        data->exit_status = ft_export(data, arg);
    else if (!ft_strncmp(cmd, "unset", 5))
        data->exit_status = ft_unset(data, arg);
    else if (!ft_strncmp(cmd, "cd", 2))
        data->exit_status = cd(data, arg);
    else if (!ft_strncmp(cmd, "exit", 4))
        exit_shell(data, str);
    else
        data->exit_status = path(data, cmd, arg);
    //printf("exit_status = %d\n", data->exit_status);
    return (0);
}