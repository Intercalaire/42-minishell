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

void	init_data(t_data *data)
{
	data->command = malloc(sizeof(t_command));
	data->command->arg = NULL;
	data->command->cmd = NULL;
	data->command->lign = NULL;
	data->output = malloc(sizeof(t_output));
	data->output->h_doc = NULL;
	data->output->infile = NULL;
	data->output->outfile = NULL;
	data->output->outfile_append = NULL;
	data->count = 0;
	data->size = 0;
	data->nbr_pipe = 0;
	data->nbr_arg = 0;
}
