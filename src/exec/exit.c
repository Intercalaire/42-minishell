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
#include <limits.h>

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static long long	ft_atol(char *str, int *error)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	sign = check_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
				&& str[i] - '0' > LLONG_MAX % 10))
		{
			if (sign == 1)
				*error = 1;
			else
				*error = 1;
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

long long	get_exit_code(t_data *data, char **arg)
{
	long long	exit_code;
	int 		error;

	error = 0;
	if (!arg || !*arg)
		exit_code = data->exit_status;
	else
	{
		if (is_valid_number(arg[0]))
		{
			exit_code = ft_atol(arg[0], &error);
			if (error == 1)
			{
				printf("minishell: exit: %s: ", arg[0]);
				printf("numeric argument required\n");
				exit_code = 2;
			}
			else
				exit_code = exit_code % 256;
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", arg[0]);
			exit_code = 2;
		}
	}
	return (exit_code);
}

void	exit_shell(t_data *data, char **arg)
{
	long long	exit_code;
	if (data->meter->nbr_pipe == 0)
		printf("exit\n");
	if (arg && *arg && **arg)
		exit_code = get_exit_code(data, arg);
	else
		exit_code = data->exit_status;
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
	ft_end_error_prog(data);
	exit(exit_code);
}
