/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:23:41 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/03 18:23:43 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static int	double_output(t_data *data, char *str);
static int	double_output_utils(t_data *data, char *str, int i);

int	special_char(t_data *data, char *str)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && in_quote == 1)
			in_quote = 0;
		if ((str[i] == '\'' || str[i] == '"') && in_quote == 0)
			in_quote = 1;
		if ((str[i] == ';' || str[i] == '\\'
				|| str[i] == '&' || str[i] == '*') && in_quote == 0)
		{
			ft_little_error_prog(data, str, TOKEN, str[i]);
			return (1);
		}
		i++;
	}
	if (double_output(data, str) == 1)
	{
		return (1);
	}
	return (0);
}

static int	double_output(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (double_output_utils(data, str, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

static int	double_output_utils(t_data *data, char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == ' ' && str[i + 2] == '>')
	{
		ft_little_error_prog(data, str, TOKEN, str[i]);
		return (1);
	}
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
	{
		ft_little_error_prog(data, str, TOKEN, str[i]);
		return (1);
	}
	if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
	{
		ft_little_error_prog(data, str, TOKEN, str[i]);
		return (1);
	}
	if (str[i] == '<' && str[i + 1] == ' ' && str[i + 2] == '<')
	{
		ft_little_error_prog(data, str, TOKEN, str[i]);
		return (1);
	}
	return (0);
}
