/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable_more_more_utils.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 04:35:29 by vgodart           #+#    #+#             */
/*   Updated: 2024/07/18 04:35:31 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

char	*ft_itoa_free(int n, char *to_free)
{
	char	*str;

	str = ft_itoa(n);
	free(to_free);
	return (str);
}

char	*ft_strdup_free(const char *s, char *to_free)
{
	char	*str;

	str = ft_strdup(s);
	free(to_free);
	return (str);
}

int	count_dollar_not_in_quotes(char *str)
{
	int	i;
	int	count;
	int	in_quote_simple;
	int	in_quote_double;

	i = 0;
	count = 0;
	in_quote_simple = 0;
	in_quote_double = 0;
	while (str[i])
	{
		if (in_quote_simple == 0 && str[i] == '\'')
			in_quote_simple = 1;
		else if (in_quote_simple == 1 && str[i] == '\'')
			in_quote_simple = 0;
		else if (in_quote_double == 0 && str[i] == '"')
			in_quote_double = 1;
		else if (in_quote_double == 1 && str[i] == '"')
			in_quote_double = 0;
		if (str[i] == '$' && in_quote_double == 0)
			count++;
		i++;
	}
	return (count);
}

char	*substr_to_next_dollar(char *str)
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
	value = ft_strndup(str + start, i - start);
	return (value);
}

char	*ev_normal_used(t_data *data, char *str, char *tmp, int quote)
{
	char	*value;
	int		index_end_var;

	value = make_the_char(data, str);
	if (ft_strchr(str, '"'))
	{
		index_end_var = get_index_end_env_var(str + 1);
		free(value);
		value = ft_substr(str, 0, index_end_var);
	}
	if (tmp)
		free(tmp);
	if (value == NULL)
		return (NULL);
	return (env_var_utils(data, value, quote));
}
