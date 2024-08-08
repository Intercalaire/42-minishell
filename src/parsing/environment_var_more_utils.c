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

static char	*ft_strdup_condition_utils(char *s, char *str, int *j, int *k);

char	*ft_strdup_condition(char *s, char *str, int *j, int *k)
{
	if (s[*k] == '$' && !s[*k + 1])
		str[*j++] = s[*k++];
	if (s[*k] == '$' && s[*k + 1] == '$')
	{
		str[*j++] = s[*k++];
		str[*j++] = s[*k++];
	}
	return (ft_strdup_condition_utils(s, str, j, k));
}

static char	*ft_strdup_condition_utils(char *s, char *str, int *j, int *k)
{
	int	z;

	z = *k;
	while (s[z] && s[z] != '$')
		z++;
	if (s[z] == '$' && (s[z + 1] == '\'' || s[z + 1] == '\"'))
	{
		if (s[*k + 1] == '\'' && s[*k + 2] == '$')
		{
			(*k) += 2;
			while (s[*k] && s[*k] != '\'')
			{
				str[(*j)++] = s[(*k)++];
			}
			if (s[*k] == '\'')
				(*k)++;
		}
		else
		{
			str[(*j)++] = s[(*k)++];
			if (s[*k] == '\'' || s[*k] == '\"')
				str[(*j)++] = s[(*k)++];
		}
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

char	*ev_simple_used(t_data *data, char *str, char *tmp)
{
	char	*value;

	value = make_the_char(data, str);
	if (tmp)
		free(tmp);
	if (value == NULL)
		return (NULL);
	return (value);
}
