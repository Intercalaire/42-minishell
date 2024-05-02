/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:29:23 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/02 17:29:26 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

int pars_pipe(t_data *data)
{
	t_data *new_arg;

	while(*data->arg)
	{
		if (*data->arg == "|")
		{
			new_arg = malloc(sizeof(t_data));
    		init_data(new_arg);
    		
		}
	}
}