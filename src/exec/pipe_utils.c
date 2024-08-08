/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 05:21:38 by hsolet            #+#    #+#             */
/*   Updated: 2024/08/08 05:21:40 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

void	close_secure(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close_fd(i);
		i++;
	}
}

int	close_fd(int fd)
{
	if (fd != -1)
	{
		close(fd);
		return (0);
	}
	return (1);
}
void do_wait(t_data *data)
{
	int status;
	int i;

	i = 0;
	while (i <= data->meter->nbr_pipe)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			data->exit_status = 1;
		}
		else
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
		}
		i++;
	}
}
int do_pipe(t_data *data, int *pipefd)
{
	int i;
	
	i = 0;
	while (i <= data->meter->nbr_pipe)
	{
		if (i != data->meter->nbr_pipe)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				return (1);
			}
		}
		if (execute_fork(data, i, pipefd))
			return (1);
		i++;
	}
	return (0);
}