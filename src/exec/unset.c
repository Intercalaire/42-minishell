/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:13:30 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/29 09:59:22 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static void	free_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (data->env[i])
		i++;
	while (i >= 0)
	{
		free(env[i]);
		i--;
	}
	free(env);
}

static void	remove_var(t_data *data, int env_index, char **new_env)
{
	int	j;

	if (env_index == -1)
	{
		free(new_env);
		return ;
	}
	j = 0;
	while (j < env_index)
	{
		new_env[j] = ft_strdup(data->env[j]);
		j++;
	}
	while (data->env[j + 1])
	{
		new_env[j] = ft_strdup(data->env[j + 1]);
		j++;
	}
	ft_free_strtab(data->env);
	data->env = cpy_envir(new_env);
	free_env(data, new_env);
}

static int unset_utils(t_data *data, char *arg, char *key, char **new_env)
{
	int	env_index;

	if (arg[0] == '-')
	{
		print_error("Minishell: unset: ", arg, ": invalid option.");
		if (key)
			free(key);
		if (new_env)
			ft_free_strtab(new_env);
		return (2);
	}
	if (ft_isalnum(arg[0]))
	{
		key = ft_strdup(arg);
		env_index = search_env(data, key);
		remove_var(data, env_index, new_env);
		free(key);
	}
	return (0);
}

int	ft_unset(t_data *data, char **arg)
{
	int		i;
	int		j;
	char	*key;
	char	**new_env;

	i = 0;
	key = NULL;
	if (!*arg)
		return (0);
	while (arg[i])
	{
		j = 0;
		while (data->env[j])
			j++;
		new_env = ft_calloc((j), sizeof(char *));
		if (!new_env)
			return (1);
		if (unset_utils(data, arg[i], key, new_env) == 2)
			return (2);
		i++;
	}
	return (0);
}
