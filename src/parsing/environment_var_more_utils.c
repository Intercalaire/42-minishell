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
// static int	ft_count_char(char *str, char c);


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

// static int	ft_count_char(char *str, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (str && str[i])
// 	{
// 		if (str[i] == c)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

int calloc_search_env(t_data *data, const char *str)
{
	int i = 0;
	// int count = 0;
	// int len = 0;

	// len = 0;
	// if (ft_count_char((char *)str, '$') >= 2)
	// {
	// 	while (str && str[i])
	// 	{
	// 		len += ft_strlen(make_the_char(data, (char *)str + i));
	// 		i++;
	// 	}
	// }
	// else if (ft_count_char((char *)str, '$') == 1)
	// {
	i = search_env(data, (char *)str + 1);
	if (i == -1)
		return (-1);
	return (ft_strlen(data->env[i]));
	// }
	// else
		// return (2);
	// return (2);
}
