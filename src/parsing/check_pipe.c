/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:51:04 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/13 15:51:07 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static int	look_pipe_helper(t_data *data, char *str, int i);

int	look_pipe(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
	{
		ft_little_error_prog(data, str, PIPE);
		return (1);
	}
	if (look_pipe_helper(data, str, i) == 1)
		return (1);
	return (0);
}

static int	look_pipe_helper(t_data *data, char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				ft_little_error_prog(data, str, PIPE);
				return (1);
			}
		}
		i++;
	}
	if (i > 0 && str[i - 1] == '|')
	{
		ft_little_error_prog(data, str, PIPE);
		return (1);
	}
	return (0);
}
