/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 08:46:17 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/30 14:37:55 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static long long	check_error(int error, char *arg, long long exit_code)
{
	if (error == 1)
	{
		print_error("Minishell: exit: ", arg, ": Numeric argument required");
		return (2);
	}
	else
		return (exit_code % 256);
	return (0);
}

long long	get_exit_code(t_data *data, char **arg)
{
	long long	exit_code;
	int			error;

	error = 0;
	if (!arg || !*arg)
		exit_code = data->exit_status;
	else
	{
		if (is_valid_number(arg[0]) || arg[0][0] == '-' || arg[0][0] == '+'
			|| arg[0][0] == ' ' || arg[0][0] == '\t' || arg[0][0] == '\n'
			|| arg[0][0] == '\v' || arg[0][0] == '\r' || arg[0][0] == '\f')
		{
			exit_code = ft_atol(arg[0], &error);
			exit_code = check_error(error, arg[0], exit_code);
		}
		else
		{
			print_error("Minishell: exit: ", arg[0],
				": Numeric argument required");
			exit_code = 2;
		}
	}
	return (exit_code);
}

static void	close_files(t_data *data)
{
	if (data->fd_pipe->std_in > -1)
	{
		dup2(data->fd_pipe->std_in, STDIN_FILENO);
		close(data->fd_pipe->std_in);
	}
	if (data->fd_pipe->std_out > -1)
	{
		dup2(data->fd_pipe->std_out, STDOUT_FILENO);
		close(data->fd_pipe->std_out);
	}
}

void	exit_shell(t_data *data, char **arg)
{
	long long	exit_code;

	close_files(data);
	if (data->meter->nbr_pipe == 0)
		ft_putstr_fd("exit\n", 2);
	if (arg && *arg && **arg)
		exit_code = get_exit_code(data, arg);
	else
		exit_code = data->exit_status;
	if (arg && arg[1] && exit_code != 2)
	{
		ft_putstr_fd("Minishell: exit: Too many arguments\n", 2);
		data->exit_status = 1;
		return ;
	}
	ft_end_error_prog(data);
	exit(exit_code);
}
