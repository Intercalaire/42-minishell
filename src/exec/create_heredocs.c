/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 05:03:50 by hsolet            #+#    #+#             */
/*   Updated: 2024/08/08 05:03:56 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static char	*get_env_value(t_data *data, char *varname)
{
	int		index;
	char	*entry;
	char	*value;

	index = search_env(data, varname);
	if (index == -1)
		return (NULL);
	entry = data->env[index];
	value = ft_strchr(entry, '=');
	if (!value)
		return (NULL);
	return (value + 1);
}

static int	handle_special_case(t_data *data, char **ptr)
{
	int	size;

	size = ft_strlen(ft_itoa(data->exit_status));
	*ptr += 2;
	return (size);
}

static int	handle_env_var(t_data *data, char **ptr)
{
	char	*end;
	int		len;
	char	varname[256];
	char	*value;

	end = *ptr + 1;
	while (ft_isalnum(*end) || *end == '_')
		end++;
	len = end - (*ptr + 1);
	if (len > 0)
	{
		strncpy(varname, *ptr + 1, len);
		varname[len] = '\0';
		value = get_env_value(data, varname);
		*ptr = end;
		if (value)
			return (ft_strlen(value));
		else
			return (0);
	}
	*ptr = end;
	return (0);
}

int	calculate_size_needed(t_data *data, char *line)
{
	int		size_needed;
	char	*ptr;

	size_needed = 1;
	ptr = line;
	while (*ptr)
	{
		if (*ptr == '$')
		{
			if (*(ptr + 1) == '?')
				size_needed += handle_special_case(data, &ptr);
			else
				size_needed += handle_env_var(data, &ptr);
		}
		else
		{
			size_needed++;
			ptr++;
		}
	}
	return (size_needed);
}

void	handle_env_var_two(t_data *data, char **temp, char **ptr)
{
	char	*end;
	int		len;
	char	varname[256];
	char	*value;

	end = *ptr + 1;
	while (ft_isalnum(*end) || *end == '_')
		end++;
	len = end - (*ptr + 1);
	if (len > 0)
	{
		ft_strncpy(varname, *ptr + 1, len);
		varname[len] = '\0';
		value = get_env_value(data, varname);
		if (value)
		{
			ft_strncpy(*temp, value, ft_strlen(value));
			*temp += ft_strlen(value);
		}
	}
	*ptr = end;
}
