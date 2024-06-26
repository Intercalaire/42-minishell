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
	printf("%s `%c'\n", msg, token);
	free(str);
	if (data)
	{
		free(data->command);
		free(data->output);
		free(data->meter);
	}
}

void	ft_little_error_prog_quote(t_data *data, char *str, char *msg)
{
	printf("%s\n", msg);
	free(str);
	if (data)
	{
		free(data->command);
		free(data->output);
		free(data->meter);
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
	}
}

void	ft_end_error_prog(t_data *data, char *str, char *msg)
{
	printf("%s\n", msg);
	if (data)
	{
		ft_free_data(data, str);
		free(data);
	}
}
