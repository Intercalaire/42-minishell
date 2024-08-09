/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:53:46 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/29 09:49:11 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static void	realloc_env(t_data *data)
{
	int		i;
	char	**new_env;

	i = 0;
	while (data->env[i])
		i++;
	new_env = ft_calloc((i + 2), sizeof(char *));
	if (!new_env)
		return ;
	i = 0;
	while (data->env[i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		i++;
	}
	new_env[i] = ft_strdup("");
	ft_free_strtab(data->env);
	cpy_env(data, new_env);
	ft_free_strtab(new_env);
}

void	add_env(t_data *data, char *key, char *value)
{
	int		i;
	char	*new_env;
	char	*tmp;

	i = 0;
	realloc_env(data);
	while (data->env[i])
		i++;
	new_env = ft_strdup(key);
	if (value)
	{
		tmp = ft_strjoin(new_env, "=");
		free(new_env);
		new_env = ft_strjoin(tmp, value);
		free(tmp);
	}
	free(data->env[i - 1]);
	data->env[i - 1] = ft_strdup(new_env);
	free(new_env);
	free(data->env[i]);
	data->env[i] = NULL;
}

void	change_env(t_data *data, char *key, char *value)
{
	int		i;
	char	*new_env;
	char	*tmp;

	i = search_env(data, key);
	if (i == -1)
	{
		add_env(data, key, value);
		return ;
	}
	new_env = ft_strdup(key);
	tmp = ft_strjoin(new_env, "=");
	free(new_env);
	new_env = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(new_env, value);
	free(new_env);
	new_env = ft_strdup(tmp);
	free(tmp);
	free(data->env[i]);
	data->env[i] = ft_strdup(new_env);
	free(new_env);
}

void	cat_env(t_data *data, char *key, char *value)
{
	int		i;
	char	*new_env;
	char	*tmp;
	char	*key_value_str;

	i = search_env(data, key);
	tmp = ft_strdup(data->env[i]);
	if (!ft_strchr(tmp, '='))
	{
		key_value_str = ft_strjoin(key, "=");
		new_env = ft_strjoin(key_value_str, value);
		free(key_value_str);
	}
	else
		new_env = ft_strjoin(tmp, value);
	free(data->env[i]);
	data->env[i] = ft_strdup(new_env);
	free(tmp);
	free(new_env);
}

char	**bubble_sort(char **arr, int n)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j + 1])) > 0)
			{
				temp = ft_strdup(arr[j]);
				free(arr[j]);
				arr[j] = ft_strdup(arr[j + 1]);
				free(arr[j + 1]);
				arr[j + 1] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		i++;
	}
	return (arr);
}
