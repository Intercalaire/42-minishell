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

static char	*environment_variable(t_data *data, char *str, char *fullstr);
static int	know_the_quote(char *str);
static char	*make_the_char(t_data *data, char *str);
static char	*ft_strdup_utils(t_data *data, const char *s, char *str, int i);

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

static char	*ft_strdup_utils(t_data *data, const char *s, char *str, int i)
{
	int		j;
	int		k;
	int		z;
	char	*env_str;

	j = 0;
	k = 0;
	env_str = NULL;
	str = ft_strdup_condition((char *)s, str, &j, &k);
	while (k < i)
	{
		if (s[k] == '$')
		{
			z = 0;
			env_str = environment_variable(data, (char *)s + k, (char *)s);
			if (env_str)
			{
				while (env_str && env_str[z])
					str[j++] = env_str[z++];
				k += data->len_env;
				free(env_str);
				env_str = NULL;
			}
			else
				str[j++] = s[k++];
		}
		else
			str[j++] = s[k++];
	}
	str[j] = '\0';
	return (ft_trim_quote(str));
}

static char	*environment_variable(t_data *data, char *str, char *fullstr)
{
	char	*value;
	int		quote;

	quote = know_the_quote(fullstr);
	if (quote < 2)
	{
		value = make_the_char(data, str);
		if (value == NULL)
			return (NULL);
		return (env_var_utils(data, value, quote));
	}
	else
	{
		value = make_the_char(data, str);
		if (value == NULL)
			return (NULL);
		return (value);
	}
	return (str);
}

static char	*make_the_char(t_data *data, char *str)
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

static int	know_the_quote(char *str)
{
	int	i;
	int	in_quote_simple;
	int	in_quote_double;

	i = 0;
	in_quote_simple = 0;
	in_quote_double = 0;
	if (str == NULL || ft_strlen(str) == 1)
		return (2);
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
