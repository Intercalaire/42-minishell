/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 08:25:53 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/22 08:26:12 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static void	change_variable(t_data *data, char **arg, char *cmd)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	if (!arg[0] && cmd)
		change_env(data, "_", cmd);
	else
		change_env(data, "_", arg[i - 1]);
}

int	exec(t_data *data, char *cmd, char **arg)
{
	if (!ft_strncmp(cmd, "echo", 5))
		data->exit_status = echo(arg);
	else if (!ft_strncmp(cmd, "pwd", 4))
		data->exit_status = pwd();
	else if (!ft_strncmp(cmd, "env", 4))
		data->exit_status = print_env(data, arg);
	else if (!ft_strncmp(cmd, "export", 7))
		data->exit_status = ft_export(data, arg);
	else if (!ft_strncmp(cmd, "unset", 6))
		data->exit_status = ft_unset(data, arg);
	else if (!ft_strncmp(cmd, "cd", 3))
		data->exit_status = cd(data, arg);
	else if (!ft_strncmp(cmd, "exit", 5))
		exit_shell(data, arg);
	else if (cmd && *cmd)
		path(data, cmd, arg);
	if (cmd || *arg)
		change_variable(data, arg, cmd);
	return (data->exit_status);
}
