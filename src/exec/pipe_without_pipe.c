/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_without_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 05:25:41 by hsolet            #+#    #+#             */
/*   Updated: 2024/08/08 05:25:45 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static int	execute_builtin_with_redir(t_data *data, char *cmd, char **arg)
{
	data->fd_pipe->std_in = dup(STDIN_FILENO);
	data->fd_pipe->std_out = dup(STDOUT_FILENO);
	if (check_open_files(data, 0))
	{
		dup2(data->fd_pipe->std_in, STDIN_FILENO);
		dup2(data->fd_pipe->std_out, STDOUT_FILENO);
		close(data->fd_pipe->std_in);
		close(data->fd_pipe->std_out);
		return (1);
	}
	exec(data, cmd, arg);
	dup2(data->fd_pipe->std_in, STDIN_FILENO);
	dup2(data->fd_pipe->std_out, STDOUT_FILENO);
	close(data->fd_pipe->std_in);
	close(data->fd_pipe->std_out);
	return (0);
}

static int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	start_process(t_data *data)
{
	if (is_builtin(data->command->cmd[0]) || !data->command->cmd[0])
	{
		if (execute_builtin_with_redir(data, data->command->cmd[0],
				data->command->arg[0]))
			return (1);
	}
	else
	{
		if (exec(data, data->command->cmd[0], data->command->arg[0]))
		{
			return (1);
		}
	}
	return (0);
}

int	check_open_files(t_data *data, int i)
{
	int	return_value;

	return_value = 0;
	if (data->output->h_doc[i] && data->output->here_d[i] == 1)
		return_value += create_infiles_heredoc(data, i);
	if (data->output->infile[i] && data->output->here_d[i] == 0)
		return_value += create_infiles(data, i);
	if (data->output->outfile[i] && *data->output->outfile[i])
		return_value += create_outfiles(data, i);
	if (data->output->outfile_append[i] && *data->output->outfile_append[i])
		return_value += create_outfiles_append(data, i);
	if (return_value)
		data->exit_status = 1;
	return (return_value);
}
