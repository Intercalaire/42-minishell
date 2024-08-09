/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 04:51:33 by hsolet            #+#    #+#             */
/*   Updated: 2024/08/09 04:58:54 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

void	ft_free_cmd(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (i <= data->meter->nbr_pipe)
	{
		if (cmd[i])
		{
			free(cmd[i]);
			cmd[i] = NULL;
		}
		i++;
	}
	free(cmd);
}

static void	ft_free_strarg_utils(char ***tab, int i, int j)
{
	if (tab[i][j])
	{
		free(tab[i][j]);
		tab[i][j] = NULL;
	}
}

void	ft_free_strarg(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	if (tab && *tab)
	{
		while (tab[i])
		{
			j = 0;
			if (tab[i])
			{
				while (tab[i][j])
				{
					ft_free_strarg_utils(tab, i, j);
					j++;
				}
				free(tab[i]);
				tab[i] = NULL;
				i++;
			}
		}
		free(tab);
		tab = NULL;
	}
}
