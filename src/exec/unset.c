/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:13:30 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/30 10:56:41 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static void remove_var(t_data *data, int env_index, char  **new_env)
{
	int j;
	if (env_index == -1)
	{
		i++;
		continue ;
	}
    j = 0;
    while (j < env_index) 
	{
	    new_env[j] = ft_strdup(data->env[j]);
	    free(data->env[j]);
	    j++;
	}
	while (data->env[j + 1])
    {
        new_env[j] = ft_strdup(data->env[j + 1]);
        j++;
    }
    data->env = cpy_envir(new_env);
}

int ft_unset(t_data *data, char **arg)
{
    int i;
	int env_index;
	int j;
	char *key;
    char **new_env;

	i = 0;
	j = 0;
    	while (data->env[j])
    	    j++;
    	new_env = ft_calloc((j + 1), sizeof(char *));
    	if (!new_env)
		    return (1);
	while (arg[i])
	{
		key = ft_strdup(arg[i]);
    	env_index = search_env(data, key);
		remove_var(data, env_index, new_env);
		i++;
	}
	free(key);
	if (new_env)
		ft_free_strtab(new_env);
	return (0);
}
