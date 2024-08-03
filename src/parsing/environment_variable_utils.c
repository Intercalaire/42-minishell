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

char	*env_var_utils(t_data *data, char *value, int quote)
{
	int		i;
	int		value_len;
	char	*result;

	if (quote == 0 && value[1] == '\0')
		return (ft_strdup_free("", value));
	if (value[1] == '?')
		return (ft_itoa_free(data->exit_status, value));
	if (!ft_isalnum(value[1]) && value[1] != '_')
		return (value);
	i = search_env(data, value + 1);
	if (i == -1)
		return (ft_strdup_free("", value));
	if (check_dollar_stop(value) == 0)
	{
		result = char_dollar_stop(value);
		free(value);
		return (ft_strdup_free(result, result));
	}
	value_len = ft_strlen(value);
	if (!ft_strchr(data->env[i], '='))
		return (ft_strdup_free("", value));
	value = ft_strdup_free(data->env[i] + value_len, value);
	return (value);
}

int	check_dollar_stop(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && !ft_isalnum(value[i + 1]) && value[i + 1] != '_'
			&& value[i + 1] != '?' && value[i + 1] != ' ')
			return (0);
		i++;
	}
	return (2);
}

char	*char_dollar_stop(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && !ft_isalnum(value[i + 1]) && value[i + 1] != '_'
			&& value[i + 1] != '?' && value[i + 1] != ' ')
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
