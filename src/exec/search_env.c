/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:43:30 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/29 09:50:49 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/exec_test/minishell.h"
int search_env(t_data *data, char *str)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(str, data->env[i], ft_strlen(str)) == 0)
				return (i);
		i++;
	}
	return (-1);
}
