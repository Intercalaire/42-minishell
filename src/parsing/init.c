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
	data->command->next = malloc(sizeof(t_command));
	data->command->prev = malloc(sizeof(t_command));
	data->command->arg = NULL;
	data->command->cmd = NULL;
	data->command->lign = NULL;
	data->count = 0;
	data->size = 0;
	data->nbr_pipe = 0;
	data->nbr_arg = 0;
}