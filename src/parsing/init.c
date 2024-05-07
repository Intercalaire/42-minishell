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
	data->arg = NULL;
	data->next = NULL;
	data->prev = NULL;
	data->count = 0;
	data->size = 0;
}