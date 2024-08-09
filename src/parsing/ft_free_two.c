/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:25:25 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/12 16:25:27 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

void	ft_little_error_prog(t_data *data, char *str, char *msg, char token)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" `", 2);
	ft_putchar_fd(token, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd("'\n", 2);
	free(str);
	if (data)
	{
		free(data->command);
		free(data->output);
		free(data->meter);
		free(data->fd_pipe);
		free(data->env_var);
	}
}

void	ft_little_error_prog_quote(t_data *data, char *str, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free(str);
	if (data)
	{
		free(data->command);
		free(data->output);
		free(data->meter);
		free(data->fd_pipe);
		free(data->env_var);
	}
}

void	ft_little_error_prog_no_msg(t_data *data, char *str)
{
	free(str);
	if (data)
	{
		free(data->command);
		free(data->output);
		free(data->meter);
		free(data->fd_pipe);
		free(data->env_var);
	}
}

void	ft_end_error_prog(t_data *data)
{
	if (data)
	{
		ft_free_data(data, NULL);
		ft_free_strtab(data->env);
		free(data);
	}
}
