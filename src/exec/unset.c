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
#include "../../include/exec_test/minishell.h"

void ft_unset(t_data *data)
{
    int i;
	int env_index;
	int j;
	char *key;
    char **new_env;

	i = 0;
	j = 0;
	while (data->command->arg[0][i])
	{
		key = ft_strdup(data->command->arg[0][i]);
    	env_index = search_env(data, key);
		if (env_index == -1)
		{
			i++;
			continue ;
		}
    	while (data->env[j])
    	    j++;
    	new_env = ft_calloc((j), sizeof(char *));
    	if (!new_env)
    	    return ;
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
    	    free(data->env[j + 1]);
    	    j++;
    	}
    	free(data->env);
    	data->env = new_env;
		i++;
	}
}