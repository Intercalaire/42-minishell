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
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}
