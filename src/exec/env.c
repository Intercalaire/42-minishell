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

#include "../../include/parsing/minishell.h"
#include <stdio.h>

int	print_env(t_data *data, char **arg)
{
	int	i;

	i = 0;
	if (arg[0])
	{
		print_error("Minishell: env: ", arg[0], ": Too mush argument");
		return (1);
	}
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
