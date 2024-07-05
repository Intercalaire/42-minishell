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

void	ft_error_prog(t_data *data, char *str, char *msg)
{
	printf("%s\n", msg);
	ft_free_data(data, str);
	exit(EXIT_FAILURE);
}

void	ft_free_data(t_data *data, char *str)
{
	if (data->command)
	{
		if (data->command->lign)
			ft_free_strtab(data->command->lign);
		if (data->command->arg)
			ft_free_strarg(data->command->arg);
		if (data->command->cmd)
			ft_free_strtab(data->command->cmd);
		free(data->command);
	}
	if (data->output)
	{
		if (data->output->h_doc)
			ft_free_strarg(data->output->h_doc);
		if (data->output->infile)
			ft_free_strarg(data->output->infile);
		if (data->output->outfile)
			ft_free_strarg(data->output->outfile);
		if (data->output->outfile_append)
			ft_free_strarg(data->output->outfile_append);
		if (data->output->append)
		{
			free(data->output->append);
			data->output->append = NULL;
		}
		if (data->output->here_d)
		{
			free(data->output->here_d);
			data->output->here_d = NULL;
		}
		free(data->output);
	}
	if (data->meter)
		free(data->meter);
	if (data->fd_pipe)
		free(data->fd_pipe);
	free(str);
	str = NULL;
}

void	ft_free_strtab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	free(tab);
	tab = NULL;
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
					if (tab[i][j])
					{
						free(tab[i][j]);
						tab[i][j] = NULL;
					}
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
