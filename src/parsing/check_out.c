/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:28:41 by vgodart           #+#    #+#             */
/*   Updated: 2024/07/05 14:28:42 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static int	check_symbols(t_data *data, char *str);
static int	check_last_character(t_data *data, char *str);
static int	check_next_chars(t_data *data, char *str, int *i);

static int	check_last_character(t_data *data, char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == '>' || str[len - 1] == '<')
	{
		if ((str[len - 1] == '>' && str[len - 2] == '>') || (str[len - 1] == '<'
				&& str[len - 2] == '<'))
			ft_little_error_prog_quote(data, str, OUT);
		else
			ft_little_error_prog(data, str, OUT_MORE, str[len - 1]);
		return (1);
	}
	return (0);
}

static int	check_next_chars(t_data *data, char *str, int *i)
{
	int	len;

	len = ft_strlen(str);
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
			|| str[*i] == '\v' || str[*i] == '\r' || str[*i] == '\f'))
		(*i)++;
	if (str[*i] && (str[*i] == '|' || (str[*i + 1] && str[*i + 1] == '|'))
		&& (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
			|| str[*i] == '\v' || str[*i] == '\r' || str[*i] == '\f'
			|| str[*i] == '|'))
	{
		ft_little_error_prog_quote(data, str, PIPE);
		return (1);
	}
	if ((len - 1) == (*i - 1) && (str[*i - 1] == '\t' || str[*i - 1] == '\n'
			|| str[*i - 1] == '\v' || str[*i - 1] == '\r' || str[*i - 1] == '\f'
			|| str[*i - 1] == '|'))
	{
		ft_little_error_prog_quote(data, str, OUT);
		return (1);
	}
	return (0);
}

static int	check_symbols(t_data *data, char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
		{
			if (quote == str[i])
				quote = 0;
			else
				quote = str[i];
		}
		else if (quote == 0 && (str[i] == '>' || str[i] == '<'))
		{
			if (str[++i] && (str[i] == '>' || str[i] == '<'))
				i++;
			if (check_next_chars(data, str, &i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	look_out(t_data *data, char *str)
{
	if (check_last_character(data, str))
		return (1);
	if (check_out_following(data, str) == 1)
		return (1);
	return (check_symbols(data, str));
}
