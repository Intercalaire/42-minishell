/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_more_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 03:12:23 by hsolet            #+#    #+#             */
/*   Updated: 2024/08/09 03:12:25 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

void	signal_traitment(t_data *data, int term_sig)
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

int	parent_process(t_data *data, pid_t pid)
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

char	*do_path(char *cmd, char **var, int i)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(var[i], "/");
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	ft_free_strtab(var);
	return (path);
}
