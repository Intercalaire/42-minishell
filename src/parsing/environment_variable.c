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

/*
int	error_code(t_data *data, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				printf("%d\n", data->exit_status);
				i += 2;
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	return (0);
}


int	environment_variable(t_data *data, char *str)
{
	int		i;
	int		j;
	char	*var;
	char	*value;
	char	*tmp;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				tmp = ft_itoa(data->exit_status);
				value = ft_strdup(tmp);
				free(tmp);
				i++;
			}
			else
			{
				while (str[i] && str[i] != ' ' && str[i] != '$')
				{
					i++;
					j++;
				}
				var = ft_substr(str, i - j, j);
				value = get_env_value(data, var);
				free(var);
			}
			tmp = ft_strjoin(str, value);
			free(str);
			str = tmp;
			free(value);
		}
		else
			i++;
	}
	return (0);
}
*/