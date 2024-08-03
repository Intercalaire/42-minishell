/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable_more_more_more_utils          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 05:29:24 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/03 05:29:26 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static char	*c_utils(t_data *data, char *substr, char *finalstr, int result);
static int	c_index_of_end(char *str, int i, int index_of_end);
static int	calloc_search_env_result(int i, char *finalstr);

int	calloc_search_env(t_data *data, const char *str)
{
	int		i;
	int		index_of_end;
	char	*substr;
	int		result;
	char	*finalstr;

	i = 0;
	index_of_end = 0;
	substr = NULL;
	finalstr = NULL;
	if (!data || !str || !ft_strchr(str, '$'))
		return (-1);
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (!str[i])
			break ;
		index_of_end = c_index_of_end((char *)str, i, index_of_end);
		substr = ft_substr(str, i + 1, index_of_end - i - 1);
		result = search_env(data, (char *)substr);
		finalstr = c_utils(data, substr, finalstr, result);
		i = index_of_end;
	}
	return (calloc_search_env_result(i, finalstr));
}

static int	c_index_of_end(char *str, int i, int index_of_end)
{
	if (str && !str[i + 1])
		index_of_end = 0;
	index_of_end = i + 1;
	while (str[index_of_end]
		&& (ft_isalnum(str[index_of_end]) || str[index_of_end] == '_'))
		index_of_end++;
	return (index_of_end);
}

static int	calloc_search_env_result(int i, char *finalstr)
{
	i = ft_strlen(finalstr);
	free(finalstr);
	if (i != 0)
		return (i);
	return (-1);
}

static char	*c_utils(t_data *data, char *substr, char *finalstr, int result)
{
	if (substr)
		free(substr);
	if (result != -1 && finalstr)
		finalstr = ft_strjoin_free(finalstr, data->env[result], finalstr);
	else if (result != -1 && !finalstr)
		finalstr = ft_strdup(data->env[result]);
	else if (result == -1 && finalstr)
		finalstr = ft_strjoin_free(finalstr, "", finalstr);
	return (finalstr);
}
