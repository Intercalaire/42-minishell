/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:43:30 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/29 09:50:49 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"
/*int search_env(t_data *data, char *str)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(str, data->env[i], ft_strlen(str)) == 0)
				return (i);
		i++;
	}
	return (-1);
}*/
int search_env(t_data *data, char *str)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str);
    while (data->env[i])
    {
        if (ft_strncmp(str, data->env[i], len ) == 0 && (data->env[i][len] == '=' || data->env[i][len] == '\0'))
            return (i);
        i++;
    }
    return (-1);
}

