/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:11:10 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/08 07:11:12 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

void	toggle_quotes(char c, bool *in_single_quote, bool *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

int	check_following_char(t_data *data, char *str, char current, char next)
{
	int	j;

	j = data->co_utils + 1;
	while (str[j] != '\0' && is_whitespace(str[j]))
		j++;
	if (str[j] == next)
	{
		if (current == '>')
			current = '<';
		else
			current = '>';
		ft_little_error_prog(data, str, OUT_MORE, current);
		return (1);
	}
	return (0);
}

int	check_out_following(t_data *data, char *str)
{
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	data->co_utils = -1;
	while (str[++data->co_utils] != '\0')
	{
		toggle_quotes(str[data->co_utils], &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote)
		{
			if (str[data->co_utils] == '>' && str[data->co_utils + 1] != '>')
			{
				if (check_following_char(data, str, '>', '<'))
					return (1);
			}
			else if (str[data->co_utils] == '<'
				&& str[data->co_utils + 1] != '<')
			{
				if (check_following_char(data, str, '<', '>'))
					return (1);
			}
		}
	}
	return (0);
}
