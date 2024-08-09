/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:18:09 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/30 14:21:24 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

void	free_path(char *path, char **args)
{
	if (path != NULL)
		free(path);
	if (args && *args)
		ft_free_strtab(args);
}

static char	*create_path(t_data *data, char *cmd)
{
	char	*full_path;

	if (!cmd && data->meter->nbr_pipe)
	{
		data->exit_status = 127;
		ft_end_error_prog(data);
		return (NULL);
	}
	if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || cmd[1] == '.')))
		full_path = ft_strdup(cmd);
	else
	{
		full_path = var_path(data, cmd);
		if (!full_path)
		{
			data->exit_status = 127;
			return (NULL);
		}
	}
	return (full_path);
}

static void	child_process(t_data *data, char *full_path, char **arg, char *cmd)
{
	char	**cpy_args;

	cpy_args = NULL;
	if (!data->meter->nbr_pipe)
	{
		if (check_open_files(data, 0))
		{
			free_path(full_path, cpy_args);
			ft_end_error_prog(data);
			exit(1);
		}
	}
	cpy_args = create_args(cmd, arg);
	execution(data, cmd, cpy_args, full_path);
	exit(0);
}

static int	execution_pipe(t_data *data, char *cmd, char **arg, char *full_path)
{
	char	**cpy_args;

	if (data->meter->nbr_pipe)
	{
		cpy_args = create_args(cmd, arg);
		execution(data, cmd, cpy_args, full_path);
		free_path(full_path, cpy_args);
		return (1);
	}
	return (0);
}

void	path(t_data *data, char *cmd, char **arg)
{
	char	*full_path;
	pid_t	pid;
	char	**cpy_args;

	cpy_args = NULL;
	full_path = create_path(data, cmd);
	if (!full_path)
		return ;
	data->sig_status = 1;
	if (execution_pipe(data, cmd, arg, full_path))
		return ;
	pid = fork();
	if (ft_sig(data))
	{
		free_path(full_path, cpy_args);
		return ;
	}
	if (pid == 0)
		child_process(data, full_path, arg, cmd);
	else
	{
		free_path(full_path, cpy_args);
		if (parent_process(data, pid))
			return ;
	}
}
