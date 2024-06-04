/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:19:50 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/30 10:28:05 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "../../include/exec_test/minishell.h"
/*
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
*/
int	pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX))
	{
		printf("%s\n", pwd);
		return (0);
	}
	else
		return (-1);
}

void cpy_env(t_data *data, char **environnement)
{
	int len_env;
	int i;

	i = 0;
	len_env = 0;
	while (environnement[len_env])
		len_env++;
	data->env = ft_calloc(len_env + 1, sizeof(char *));
	if (!data->env)
		return ;
		//exit_error("Alloc Error\n");
	while (environnement[i])
	{
		data->env[i] = strdup(environnement[i]);
		if (!data->env[i])
			//exit_error("Alloc Error\n");
			return ;
		i++;
	}
}
