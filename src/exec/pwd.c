/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:19:50 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/10 15:15:52 by hsolet           ###   ########.fr       */
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

int pwd(void)
{
	int i;

	while (env_cpy[i])
	{
		if (ft_strncmp(env_cpy[i], "PWD=", 4) && !ft_strncmp(env_cpy[i], "OLDPWD=", 7))
		{

		}

	}
}

void env(void)
{
	t_env *env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		exit("Alloc Error\n");
	env->variable = ft_start(env[i]);
	env->value = env[i] + ft_strlen(env->variable);
}
