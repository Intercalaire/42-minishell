#include "../../include/exec_test/minishell.h"

int exec(t_data *data)
{
    char *cmd;
    int i;

    i = 0;
    cmd = ft_strdup(data->command->cmd[i]);
    if (!ft_strncmp(cmd, "echo", 4))
        echo(data);
    else if (!ft_strncmp(cmd, "pwd", 3))
        pwd();
    else if (!ft_strncmp(cmd, "env", 3))
        print_env(data);
    else if (!ft_strncmp(cmd, "export", 6))
        ft_export(data);
    else if (!ft_strncmp(cmd, "unset", 5))
        ft_unset(data);
    else if (!ft_strncmp(cmd, "cd", 2))
        cd(data);
    else
        path(data);
    return (0);
}
