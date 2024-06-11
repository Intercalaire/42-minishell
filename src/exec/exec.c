#include "../../include/exec_test/minishell.h"

int exec(t_data *data, char *cmd, char **arg)
{
    int i;

    i = 0;
    if (!ft_strncmp(cmd, "echo", 4))
        echo(data, arg);
    else if (!ft_strncmp(cmd, "pwd", 3))
        pwd();
    else if (!ft_strncmp(cmd, "env", 3))
        print_env(data);
    else if (!ft_strncmp(cmd, "export", 6))
        ft_export(data, arg);
    else if (!ft_strncmp(cmd, "unset", 5))
        ft_unset(data, arg);
    else if (!ft_strncmp(cmd, "cd", 2))
        cd(data, arg);
    else
        path(data, cmd, arg);
    return (0);
}