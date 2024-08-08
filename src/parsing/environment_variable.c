/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:28:19 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/07 14:28:21 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

char	*ft_strdup_2(t_data *data, const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str = NULL;
	i = ft_strlen((char *)s);
	j = calloc_search_env(data, s);
	if (ft_find_char((char *)s, '$') == 1 && know_the_delim_quote((char *)s) > 2
		&& j != -1)
	{
		str = ft_calloc((i + j + 1), sizeof(char));
		if (str == NULL)
			return (NULL);
	}
	else if (j <= 0)
	{
		str = ft_calloc((i + 2), sizeof(char));
		if (str == NULL)
			return (NULL);
	}
	return (ft_strdup_utils(data, s, str, i));
}

char	*environment_variable(t_data *data, char *str, char *fullstr)
{
	int		quote;
	int		number_dollar;
	char	*tmp;

	tmp = NULL;
	quote = know_the_quote(fullstr);
	number_dollar = count_dollar_not_in_quotes(str);
	if (number_dollar > 1 && quote > 0)
	{
		tmp = substr_to_next_dollar(str);
		quote = know_the_quote(tmp);
		str = tmp;
	}
	if (quote < 2)
		return (ev_normal_used(data, str, tmp, quote));
	else
		return (ev_simple_used(data, str, tmp));
	return (str);
}

char	*make_the_char(t_data *data, char *str)
{
	int		i;
	int		start;
	char	*value;

	i = 0;
	value = NULL;
	while (str[i] && str[i] != '$')
		i++;
	start = i;
	i++;
	while (str[i] && ft_ischar_no_quotes(str[i]) == 1 && str[i] != '$')
		i++;
	data->len_env = i - start;
	value = ft_strndup(str + start, i - start);
	return (value);
}

int	know_the_quote(char *str)
{
	int	i;
	int	in_quote_simple;
	int	in_quote_double;

	i = 0;
	in_quote_simple = 0;
	in_quote_double = 0;
	if (str == NULL || ft_strlen(str) == 1)
		return (2);
	while (str[i] == '$' && str[ft_strlen(str) - 1] == '\'')
		i++;
	while (str[i] && str[i] != '$')
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
	return (ktq_utils(in_quote_double, in_quote_simple));
}
