/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_pars_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:51:06 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/25 10:51:08 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

// static void	count_args(t_data *data, int i)
// {
// 	data->nbr_arg = 0;
// 	while (data->command->lign[i] && *data->command->lign[i] != '|')
// 	{
// 		data->nbr_arg++;
// 		i++;
// 	}
// }

// static int handle_command_assignment(t_data *data, int *i, int *y, int *z) {
// 	if (!data->command->cmd[*y]) {
// 		data->command->cmd[*y] = ft_strdup_2(data, data->command->lign[(*i)]);
// 		if (!data->command->cmd[*y]) {
// 			ft_free_data_no_str(data);
// 			return 2;
// 		}
// 	} else {
// 		data->command->arg[*y][*z] = ft_strdup_2(data, data->command->lign[(*i)]);
// 		if (!data->command->arg[*y][*z]) {
// 			ft_free_data_no_str(data);
// 			return 2;
// 		}
// 		printf("arg[%d][%d] : %s\n", *y, *z, data->command->arg[*y][*z]);
// 		(*z)++;
// 	}
// 	return 0;
// }

// static int process_command_line(t_data *data, int *i, int *y, int *z) {
// 	if (data->command->lign[(*i)] && data->command->lign[(*i) + 1]) {
// 		if (verif_lign(data, data->command->lign[(*i)]) == 0) {
// 			(*i)++;
// 			verif_output(data, y, data->command->lign[(*i)]);
// 		} else {
// 			return handle_command_assignment(data, i, y, z);
// 		}
// 	} else {
// 		return handle_command_assignment(data, i, y, z);
// 	}
// 	(*i)++;
// 	return 0;
// }

// int handle_args(t_data *data, int *i, int *y, int *z)
// {
// 	count_args(data, *i);
// 	count_all(data, y, *i);

// 	while (data->command->lign[(*i)] && *data->command->lign[(*i)] != '|') {
// 		int result = process_command_line(data, i, y, z);
// 		if (result != 0) return result;
// 	}
// 	printf("\nError here\n");
// 	return 0;
// }