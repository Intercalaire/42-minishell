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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>


static void	signal_traitment(t_data *data, int term_sig)
{
	if (term_sig == SIGSEGV)
	{
		ft_putstr_fd("Segmentation fault\n", 2);
		data->exit_status = 128 + SIGSEGV;
	}
	else if (term_sig == SIGINT)
		data->exit_status = 128 + SIGINT;
	else if (term_sig == SIGABRT)
		data->exit_status = 128 + SIGABRT;
	else if (term_sig == SIGFPE)
		data->exit_status = 128 + SIGFPE;
	else if (term_sig == SIGILL)
		data->exit_status = 128 + SIGILL;
	else if (term_sig == SIGTERM)
		data->exit_status = 128 + SIGTERM;
}

static int	parent_process(t_data *data, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		data->exit_status = 1;
	}
	else
	{
		if (WIFEXITED(status))
			{
				data->exit_status = WEXITSTATUS(status);
				return (1);
			}
		else if (WIFSIGNALED(status))
			signal_traitment(data, WTERMSIG(status));
	}
	return (0);
}

void	free_path(char *path, char **args)
{
	if (path != NULL)
		free(path);
	if (args && *args)
		ft_free_strtab(args);
}

int check_open_files(t_data *data, int i);

void	path(t_data *data, char *cmd, char **arg)
{
	char	*full_path;
	pid_t	pid;
	char	**cpy_args;

	cpy_args = NULL;
	if (!cmd && data->meter->nbr_pipe)
	{
		data->exit_status = 127;
		ft_end_error_prog(data);
		return ;
	}
	if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || cmd[1] == '.')))
        full_path = ft_strdup(cmd);
    else
    {
		full_path = var_path(data, cmd);
		if (!full_path)
		{
			data->exit_status = 127;
			return ;
		}
	}
	data->sig_status = 1;
	if (data->meter->nbr_pipe)
	{
		cpy_args = create_args(cmd, arg);
		execution(data, cmd, cpy_args, full_path);
		free_path(full_path, cpy_args);
		return ;
	}

	pid = fork();
	if (!full_path)
		return ;
	if (ft_sig(data))
	{
		free_path(full_path, cpy_args);
		return ;
	}
	if (pid == 0)
	{
		if (!data->meter->nbr_pipe)
			if (check_open_files(data, 0))
			{
				free_path(full_path, cpy_args);
				ft_end_error_prog(data);
				exit(1);
			}
		cpy_args = create_args(cmd, arg);
		execution(data, cmd, cpy_args, full_path);
		exit(0);
	}
	else
	{
		free_path(full_path, cpy_args);
		if (parent_process(data, pid))
			return ;
	}
}
