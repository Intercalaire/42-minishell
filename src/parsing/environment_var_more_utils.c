/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_var_more_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 05:49:01 by vgodart           #+#    #+#             */
/*   Updated: 2024/07/10 05:49:04 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

char	*ft_strdup_condition(char *s, char *str, int *j, int *k)
{
	if (s[*k] == '$' && !s[*k + 1])
		str[*j++] = s[*k++];
	if (s[*k] == '$' && s[*k + 1] == '$')
	{
		str[*j++] = s[*k++];
		str[*j++] = s[*k++];
	}
	if (s[*k] == '$' && (s[*k + 1] == '\''  || s[*k + 1] == '\"') && s[*k + 2] == '$')
	{
		(*j)++;
		(*k)++;
		str[*j++] = s[*k++];
		str[*j++] = s[*k++];
	}
	return (str);
}

int	ft_find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2, char *to_free)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(to_free);
	return (str);
}

int calloc_search_env(t_data *data, const char *str)
{
	int i = 0;
	int	index_of_end = 0;
	char *substr = NULL;
	int	result;
	char *finalstr;

	i = 0;
	finalstr = NULL;
	if (!data || !str || !ft_strchr(str, '$'))
		return (-1);
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (!str[i])
			break ;
		if (str && !str[i + 1])
			index_of_end = 0;
		index_of_end = i + 1;
		while (ft_isalnum(str[index_of_end]))
			index_of_end++;
		substr = ft_substr(str, i + 1, index_of_end - i - 1);
		result = search_env(data, (char *)substr);
		if (substr)
			free(substr);
		if (result != -1 && finalstr)
			finalstr = ft_strjoin_free(finalstr, data->env[result], finalstr);
		else if (result != -1 && !finalstr)
			finalstr = ft_strdup(data->env[result]);
		else if (result == -1 && finalstr)
			finalstr = ft_strjoin_free(finalstr, "", finalstr);
		i = index_of_end;
	}
	i = ft_strlen(finalstr);
	free(finalstr);
	if (i != 0)
		return (i);
	return (-1);
}
