/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:28:45 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/09 04:59:28 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

void	ft_error_prog(t_data *data, char *str, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	ft_free_data(data, str);
	exit(EXIT_FAILURE);
}

void	ft_free_output(t_data *data)
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
	if (data->output->h_doc_count)
	{
		free(data->output->h_doc_count);
		data->output->h_doc_count = NULL;
	}
	free(data->output);
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
			ft_free_cmd(data, data->command->cmd);
		free(data->command);
	}
	if (data->output)
		ft_free_output(data);
	if (data->env_var)
		free(data->env_var);
	if (data->meter)
		free(data->meter);
	if (data->fd_pipe)
		free(data->fd_pipe);
	if (str)
		free(str);
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
