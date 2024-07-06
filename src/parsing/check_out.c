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

static int check_symbols(t_data *data, char *str);
static int check_last_character(t_data *data, char *str);

static int check_last_character(t_data *data, char *str)
{
	int len;

	len = ft_strlen(str);
	if (str[len - 1] == '>' || str[len - 1] == '<')
	{
		ft_little_error_prog_quote(data, str, OUT);
		return (1);
	}
	return (0);
}

static int check_symbols(t_data *data, char *str)
{
	int i;
	char quote = 0;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
		{
			if (quote == str[i])
				quote = 0;
			else if (quote == 0)
				quote = str[i];
		}
		else if (quote == 0)
		{
			if (str[i] == '>' || str[i] == '<')
			{
				if (str[i + 1] == '>' || str[i + 1] == '<')
					i++;
				while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\r' || str[i] == '\f'))
				{
					if (str[i] == '|')
					{
						ft_little_error_prog_quote(data, str, PIPE);
						return (1);
					}
					i++;
				}
			}
		}
		i++;
	}
	return (0);
}

int look_out(t_data *data, char *str)
{
	if (check_last_character(data, str))
		return (1);
	return check_symbols(data, str);
}
