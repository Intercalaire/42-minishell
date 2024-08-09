/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:10:52 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/15 10:42:53 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

void	duplicate_stdin(t_data *data, int i)
{
	if (i != 0)
	{
		if (dup2(data->fd_pipe->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close_fd(data->fd_pipe->fd_in);
	}
}

void	child_processus(t_data *data, int *pipefd, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	duplicate_stdin(data, i);
	if (i != data->meter->nbr_pipe)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close_fd(pipefd[1]);
		close_fd(pipefd[0]);
	}
	if (check_open_files(data, i))
	{
		ft_end_error_prog(data);
		exit(EXIT_FAILURE);
	}
	exec(data, data->command->cmd[i], data->command->arg[i]);
}

int	parent_processus(t_data *data, int *pipefd, int i)
{
	if (i != 0)
		close(data->fd_pipe->fd_in);
	if (i != data->meter->nbr_pipe)
	{
		close(pipefd[1]);
		data->fd_pipe->fd_in = pipefd[0];
	}
	return (0);
}

int	execute_fork(t_data *data, int i, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (2);
	}
	if (pid == 0)
	{
		child_processus(data, pipefd, i);
		ft_end_error_prog(data);
		exit(0);
	}
	else if (parent_processus(data, pipefd, i))
		return (1);
	return (0);
}

int	my_pipe(t_data *data)
{
	int	pipefd[2];
	int	i;

	data->fd_pipe->fd_in = 0;
	i = 0;
	while (i <= data->meter->nbr_pipe)
	{
		if (data->output->h_doc[i] && *data->output->h_doc[i] != NULL)
			execute_heredoc(data, i);
		i++;
	}
	if (data->meter->nbr_pipe == 0)
	{
		if (start_process(data))
			return (1);
	}
	else
	{
		do_pipe(data, pipefd);
		do_wait(data);
	}
	return (0);
}
