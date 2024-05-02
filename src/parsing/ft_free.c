/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:28:45 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/02 15:28:46 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

void ft_error_prog(t_data *data, char *str, char *msg)
{
	printf("%s\n", msg);
	//ft_free_data(data, str);
	free(str);
	free(data);
	exit(EXIT_FAILURE);
}
void ft_free_data(t_data *data, char *str)
{
	if (data->arg)
		ft_free_strtab(data->arg);
	free(str);
}

void ft_free_strtab(char **tab)
{
	int i;

	i = 0;
	printf("free tab\n");
	while (tab[i])
	{
		//printf("tab[%d] = %s\n", i, tab[i]);
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}