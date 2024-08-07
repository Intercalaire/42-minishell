/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:10:31 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/30 15:18:07 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

char	**cpy_envir(char **env)
{
	int		i;
	int		env_len;
	char	**new_env;

	i = 0;
	env_len = 0;
	while (env[env_len])
		env_len++;
	new_env = ft_calloc((env_len + 1), sizeof(char *));
	if (!new_env)
		return (NULL);
	while (i < env_len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (new_env);
}

void	print_declare(t_data *data, int i)
{
	char	*key;
	char	*value;
	int		env_len;
	char	**new_env;

	env_len = 0;
	while (data->env[env_len])
		env_len++;
	new_env = cpy_envir(data->env);
	bubble_sort(new_env, env_len);
	while (new_env[i])
	{
		value = ft_strdup(new_env[i]);
		key = ft_strtok(new_env[i], "=");
		free(new_env[i]);
		if (ft_strlen(value) - ft_strlen(key) == 0)
			printf("declare -x %s\n", key);
		else
			printf("declare -x %s=\"%s\"\n", key, value + ft_strlen(key) + 1);
		free(key);
		free(value);
		i++;
	}
	free(new_env);
}

void	equal_sign(t_data *data, char *arg)
{
	char	*key;
	char	*value;

	key = ft_strtok(arg, "=");
	if (ft_strlen(arg) == ft_strlen(key) + 1)
		value = ft_strdup("");
	else
		value = ft_strdup(arg + ft_strlen(key) + 1);
	if (search_env(data, key) == -1)
		add_env(data, key, value);
	else
		change_env(data, key, value);
	free(key);
	if (value)
		free(value);
}

int	check_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
	{
		print_error("Minishell: export: `", arg, "': Not a valid identifier");
		return (1);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			break ;
		if (!ft_isalpha(arg[i]) && arg[i] != '_')
		{
			print_error("Minishell: export: `", arg,
				"': Not a valid identifier");
			return (1);
		}
		i++;
	}
	return (0);
}

void	plus_equal(t_data *data, char *arg)
{
	char	*key;
	char	*value;

	key = ft_strtok(arg, "+=");
	value = ft_strdup(arg + ft_strlen(key) + 2);
	if (search_env(data, key) == -1)
		add_env(data, key, value);
	else
		cat_env(data, key, value);
	free(key);
	free(value);
}
