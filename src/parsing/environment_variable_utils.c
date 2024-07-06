/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 09:51:06 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/29 09:51:08 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

int	ktq_utils(int in_qte_dble, int in_qte_sple)
{
	if (in_qte_dble == 1)
		return (1);
	if (in_qte_sple == 1)
		return (3);
	return (0);
}

char *env_var_utils(t_data *data, char *value, int quote)
{
	int	i;
	int	value_len;

	if (quote == 0 && value[1] == '\0')
		return (ft_strdup(""));
	if (value[1] == '?')
		return (ft_itoa(data->exit_status));
	if (!ft_isalnum(value[1]) && value[1] != '_')
		return (value);
	i = search_env(data, value + 1);
	if (i == -1)
		return (ft_strdup(""));
	if (check_dollar_stop(value) == 0)
		return (ft_strdup(char_dollar_stop(value)));
	value_len = ft_strlen(value);
	value = ft_strdup(data->env[i] + value_len);
	return (value);
}

int	check_dollar_stop(char *value)
{
	int	i;

	i = 0;
	while(value[i])
	{
		if (value[i] == '$' && !ft_isalnum(value[i + 1]) && value[i + 1] != '_' && value[i + 1] != '?' && value[i + 1] != ' ')
			return (0);
		i++;
	}
	return (2);
}

char	*char_dollar_stop(char *value)
{
	int	i;

	i = 0;
	while(value[i])
	{
		if (!ft_isalnum(value[i + 1]) && value[i + 1] != '_' && value[i + 1] != '?' && value[i + 1] != ' ')
			return (ft_strdup(value));
		i++;
	}
	return ("");
}

int	ft_ischar_no_quotes(int c)
{
	if (c != '"' && c != '\'')
		return (1);
	return (0);
}

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