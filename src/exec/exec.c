#include "../../include/exec_test/minishell.h"

int exec(t_data *data, char *cmd, char **arg)
{
    int i;
    int exit_status;

    i = 0;
    if (!ft_strncmp(cmd, "echo", 4))
        exit_status = echo(data, arg);
    else if (!ft_strncmp(cmd, "pwd", 3))
        exit_status = pwd();
    else if (!ft_strncmp(cmd, "env", 3))
        exit_status = print_env(data);
    else if (!ft_strncmp(cmd, "export", 6))
        exit_status = ft_export(data, arg);
    else if (!ft_strncmp(cmd, "unset", 5))
        exit_status = ft_unset(data, arg);
    else if (!ft_strncmp(cmd, "cd", 2))
        exit_status = cd(data, arg);
    else
        exit_status = path(data, cmd, arg);
    change_env(data, "?", ft_itoa(exit_status));
    return (0);
}