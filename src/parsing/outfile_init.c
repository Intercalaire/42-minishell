/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:47:39 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/28 11:47:41 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

int	outfile(t_data *data, int *y, char *str)
{
	data->output->outfile[*y][data->meter->count_outfile]
		= ft_strdup_outfile(data, str, *y, 0);
	if (!data->output->outfile[*y][data->meter->count_outfile])
	{
		ft_free_data(data, str);
		return (2);
	}
	data->meter->count_outfile++;
	return (0);
}

int	outfile_append(t_data *data, int *y, char *str)
{
	data->output->outfile_append[*y]
	[data->meter->count_outfile_append] = ft_strdup_outfile(data, str, *y, 0);
	if (!data->output->outfile_append[*y][data->meter->count_outfile_append])
	{
		ft_free_data(data, str);
		return (2);
	}
	data->meter->count_outfile_append++;
	return (0);
}

int	infile(t_data *data, int *y, char *str)
{
	data->output->infile[*y][data->meter->count_infile]
		= ft_strdup_outfile(data, str, *y, 0);
	if (!data->output->infile[*y][data->meter->count_infile])
	{
		ft_free_data(data, str);
		return (2);
	}
	data->meter->count_infile++;
	return (0);
}

int	h_doc(t_data *data, int *y, char *str)
{
	data->output->h_doc[*y][data->meter->count_h_doc]
		= ft_strdup_outfile(data, str, *y, 1);
	if (!data->output->h_doc[*y][data->meter->count_h_doc])
	{
		ft_free_data(data, str);
		return (2);
	}
	data->meter->count_h_doc++;
	return (0);
}

int	init_global(t_data *data)
{
	data->meter->nbr_pipe = data->nbr_pipe;
	data->output->h_doc = ft_calloc(data->meter->nbr_pipe + 2, sizeof(char **));
	if (!data->output->h_doc)
		return (2);
	data->output->infile
		= ft_calloc(data->meter->nbr_pipe + 2, sizeof(char **));
	if (!data->output->infile)
		return (2);
	data->output->outfile
		= ft_calloc(data->meter->nbr_pipe + 2, sizeof(char **));
	if (!data->output->outfile)
		return (2);
	data->output->outfile_append
		= ft_calloc(data->meter->nbr_pipe + 2, sizeof(char **));
	if (!data->output->outfile_append)
		return (2);
	return (0);
}
