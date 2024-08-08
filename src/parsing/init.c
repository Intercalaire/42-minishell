/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:41:52 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/30 14:41:53 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

int	g_sig = 0;
static void	init_utils(t_data *data);

int	init_data(t_data *data)
{
	data->command = malloc(sizeof(t_command));
	if (!data->command)
		return (2);
	data->meter = malloc(sizeof(t_meter));
	if (!data->meter)
		return (2);
	data->output = malloc(sizeof(t_output));
	if (!data->output)
		return (2);
	data->fd_pipe = malloc(sizeof(t_fd_pipe));
	if (!data->fd_pipe)
		return (2);
	data->env_var = malloc(sizeof(t_env_var));
	if (!data->env_var)
		return (2);
	data->command->arg = NULL;
	data->command->cmd = NULL;
	data->command->lign = NULL;
	data->output->h_doc = NULL;
	data->output->infile = NULL;
	data->output->outfile = NULL;
	data->output->outfile_append = NULL;
	data->output->here_d = NULL;
	init_utils(data);
	return (0);
}

static void	init_utils(t_data *data)
{
	data->co_utils = -1;
	data->output->append = NULL;
	data->count = 0;
	data->size = 0;
	data->len_env = 0;
	data->nbr_pipe = 0;
	data->nbr_arg = 0;
	data->sig_status = 0;
	data->output->sign = 0;
	data->meter->nbr_arg = 0;
	data->meter->nbr_pipe = 0;
	data->meter->nbr_outfile = 0;
	data->meter->nbr_h_doc = 0;
	data->meter->nbr_infile = 0;
	data->meter->nbr_outfile_append = 0;
	data->fd_pipe->fd_in = 0;
	data->fd_pipe->std_in = -1;
	data->fd_pipe->std_out = -1;
	g_sig = 0;
	data->in_quote = 0;
	data->output->h_doc_count = 0;
}
