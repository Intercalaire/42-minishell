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
static int	double_output_more_utils(t_data *data, char *str, int i);

int	special_char(t_data *data, char *str)
{
	if (double_output(data, str) == 1)
		return (1);
	return (0);
}

static int	double_output(t_data *data, char *str)
{
	int		i;
	int		in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && (in_quote == 1))
			in_quote = 0;
		if ((str[i] == '\'' || str[i] == '"') && (in_quote == 0))
			in_quote = 1;
		i++;
	}
	if (in_quote == 0)
	{
		if (double_output_utils(data, str, i) == 1)
			return (1);
	}
	return (0);
}

int	ft_strstr(char *str, char *to_find, char *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == to_find[j])
		{
			while (str[i + j] == to_find[j] && to_find[j])
				j++;
			if (to_find[j] == '\0')
			{
				*c = to_find[j - 1];
				return (1);
			}
			j = 0;
		}
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
	if (double_output_more_utils(data, str, i) == 1)
		return (1);
	return (0);
}

static int	double_output_more_utils(t_data *data, char *str, int i)
{
	char	tmp;

	tmp = 0;
	if (str[i] == '<' && str[i + 1] == ' ' && str[i + 2] == '<')
	{
		ft_little_error_prog(data, str, TOKEN, str[i]);
		return (1);
	}
	if (ft_strstr(str, ">>>", &tmp) == 1 || ft_strstr(str, "<<<", &tmp) == 1)
	{
		ft_little_error_prog(data, str, TOKEN, tmp);
		return (1);
	}
	return (0);
}
