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

static char	*environment_variable(t_data *data, char *str);

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
*/

char	*ft_strdup_2(t_data *data, const char *s)
{
	int		i;
	int		j;
	char	*str;
	char	*result;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	str = ft_calloc((i + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	if (str[0] == '$')
		str = ft_strdup(environment_variable(data, str));
	result = ft_trim_quote(str);
	free(str);
	return (result);
}

static char	*environment_variable(t_data *data, char *str)
{
	char	*value;
	int		i;

	i = search_env(data, str + 1);
	if (i == -1)
		return (str);
	value = ft_strdup(data->env[i] + ft_strlen(str));
	if (value == NULL)
		return (str);
	return (value);
}
