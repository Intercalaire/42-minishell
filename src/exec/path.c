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

static void	signal_traitment_utils(t_data *data, int term_sig)
{
	if (term_sig == SIGFPE)
	{
		printf("Erreur de calcul flottant (signal SIGFPE)\n");
		data->exit_status = 128 + SIGFPE;
	}
	else if (term_sig == SIGILL)
	{
		printf("Instruction illégale (signal SIGILL)\n");
		data->exit_status = 128 + SIGILL;
	}
	else if (term_sig == SIGTERM)
	{
		printf("Terminaison (signal SIGTERM)\n");
		data->exit_status = 128 + SIGTERM;
	}
}

static void	signal_traitment(t_data *data, int term_sig)
{
	if (term_sig == SIGSEGV)
	{
		printf("Segmentation fault\n");
		data->exit_status = 128 + SIGSEGV;
	}
	else if (term_sig == SIGINT)
		data->exit_status = 128 + SIGINT;
	else if (term_sig == SIGABRT)
	{
		printf("Abandon (signal SIGABRT)\n");
		data->exit_status = 128 + SIGABRT;
	}
	else
		signal_traitment_utils(data, term_sig);
}

static void	parent_process(t_data *data, pid_t pid)
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
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			signal_traitment(data, WTERMSIG(status));
	}
}

void	free_path(char *path, char **args)
{
	if (path)
		free(path);
	if (args)
		ft_free_strtab(args);
}

void check_open_files(t_data *data, int i);

void	path(t_data *data, char *cmd, char **arg)
{
	char	*full_path;
	pid_t	pid;
	char	**cpy_args;

	cpy_args = NULL;
	full_path = var_path(data, cmd);
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
			check_open_files(data, 0);
		cpy_args = create_args(cmd, arg);
		execution(data, cmd, cpy_args, full_path);
		// ajouter un free de tout tout tout
	}
	else
		parent_process(data, pid);
	free_path(full_path, cpy_args);
}
