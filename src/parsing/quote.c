/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:39:17 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/03 17:39:19 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static int quote_judge(t_data *data, char *str, int in_quote_double, int in_quote_simple);

int	quote_verif(t_data *data,char *str)
{
	int	i;
	int	in_quote_simple;
	int	in_quote_double;

	i = 0;
	in_quote_simple = 0;
	in_quote_double = 0;
	while(str[i])
	{
		if (in_quote_simple == 0 && str[i] == '\'' && in_quote_double == 0)
			in_quote_simple = 1;
		else if (in_quote_simple == 1 && str[i] == '\'')
			in_quote_simple = 0;
		else if (in_quote_double == 0 && str[i] == '"' && in_quote_simple == 0)
			in_quote_double = 1;
		else if (in_quote_double == 1 && str[i] == '"')
			in_quote_double = 0;
		i++;
	}
	if (quote_judge(data, str, in_quote_double, in_quote_simple) == 1)
		return (1);
	return (0);
}

static int quote_judge(t_data *data, char *str, int in_quote_double, int in_quote_simple)
{
	if (in_quote_double == 1) 
	{
		ft_little_error_prog(data, str, "unexpected EOF while looking for matching `\"'");
		return (1);
	}
	if (in_quote_simple == 1)
	{
		ft_little_error_prog(data, str, "unexpected EOF while looking for matching `\''");
		return (1);
	}
	return (0);
}
