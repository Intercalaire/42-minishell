/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:19:50 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/15 11:50:58 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void pwd(void)
{
	int i;
	char *str;

	i = 1;
	str = ft_calloc(i, sizeof(char));
	while (getcwd(str, i) == NULL)
	{
		i++;
		free(str);
		str = ft_calloc(i, sizeof(char));
	}
	printf("%s", str);
}

int pwd(t_data *data)
{
	int i;

	while (data->env[i])
	{
		if (ft_strncmp(env_cpy[i], "PWD=", 4) && !ft_strncmp(env_cpy[i], "OLDPWD=", 7))
			ft_printf("%s", ft_substr(data->env[i]))
		i++;
	}
}

void env(t_data *data, char **environnement)
{
	int len_env;
	int i;

	len_env = 0;
	while (environnement[len_env])
		len_env++;
	data->env = ft_calloc(len_env, sizeof(*char));
	if (!data->env)
		exit("Alloc Error\n");
	while (environnement[i])
	{
		env[i] = ft_strdup(environnement[len_env])
		i++;
	}
}
