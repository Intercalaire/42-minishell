/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:25:25 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/12 16:25:27 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

void	ft_little_error_prog(t_data *data, char *str, char *msg)
{
	printf("%s\n", msg);
	free(str);
	if (data)
	{
		free(data->command);
	}
}

void	ft_little_error_prog_no_msg(t_data *data, char *str)
{
	free(str);
	if (data)
	{
		free(data->command);
		free(data->output);
		free(data->meter);
	}
}

void	ft_end_error_prog(t_data *data, char *str, char *msg)
{
	printf("%s\n", msg);
	if (data)
	{
		ft_free_data(data, str);
		//free(data);
	}
}

void	ft_free_data_no_str(t_data *data)
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
		if (data->output->here_d)
			free(data->output->here_d);
		if (data->output->append)
			free(data->output->append);
		free(data->output);
	}
}