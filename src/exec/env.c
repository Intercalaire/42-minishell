/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 08:20:42 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/22 08:23:19 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../include/parsing/minishell.h"

int	print_env(t_data *data, char **arg)
{
	int	i;

	i = 0;
	if (arg[0])
	{
		printf("env: %s: Too mush argument\n", arg[0]);
		return (1);
	}
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
