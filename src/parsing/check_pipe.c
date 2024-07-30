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
static int	check_pipe_with_spaces(t_data *data, char *str, int i);

int	look_pipe(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '|')
	{
		ft_little_error_prog_quote(data, str, PIPE);
		return (1);
	}
	if (look_pipe_helper(data, str, i) == 1)
		return (1);
	return (0);
}

static int	check_pipe_with_spaces(t_data *data, char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '|')
	{
		ft_little_error_prog_quote(data, str, PIPE);
		return (1);
	}
	return (0);
}

static int	look_pipe_helper(t_data *data, char *str, int i)
{
	int	in_double_quote;
	int	in_single_quote;

	in_double_quote = 0;
	in_single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			in_double_quote = !in_double_quote;
		else if (str[i] == '\'')
			in_single_quote = !in_single_quote;
		else if (!in_double_quote && !in_single_quote && str[i] == '|')
		{
			if (check_pipe_with_spaces(data, str, i + 1))
				return (1);
		}
		i++;
	}
	if ((!in_double_quote && !in_single_quote) && i > 0 && str[i - 1] == '|')
	{
		ft_little_error_prog_quote(data, str, PIPE);
		return (1);
	}
	return (0);
}
