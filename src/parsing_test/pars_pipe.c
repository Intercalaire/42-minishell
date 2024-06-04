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

#include "../../include/exec_test/minishell.h"

static void count_args(t_data *data, int i)
{
	data->nbr_arg = 0;
	while(data->command->lign[i] && *data->command->lign[i] != '|')
	{
		data->nbr_arg++;
		i++;
	}
}

static void utils_pars_pipe(t_data *data)
{
	data->command->cmd = ft_calloc(data->nbr_pipe + 2, sizeof(char *));
	if (!data->command->cmd)
		ft_error_prog(data, "Allocation error", "Error");
	data->command->arg = ft_calloc(data->nbr_pipe + 2, sizeof(char **));
	if (!data->command->arg)
		ft_error_prog(data, "Allocation error", "Error");
}


// void pars_pipe(t_data *data)
// {
// 	int	i;
// 	int y;
// 	int z;

// 	i = 0;
// 	y = 0;
// 	utils_pars_pipe(data);
// 	while (data->nbr_pipe-- >= 0)
// 	{
// 		z = 0;
// 		data->command->cmd[y] = ft_strdup(data->command->lign[i]);
// 		i++;
// 		if (data->command->lign[i] && *data->command->lign[i] == '|') {
//             i++;
//             continue;
//         }
// 		while (data->command->lign[i] && *data->command->lign[i] != '|')
// 		{
// 			count_args(data, i);
// 			data->command->arg[y] = ft_calloc(data->nbr_arg + 1, sizeof(char *));
// 			if (!data->command->arg[y])
// 				ft_error_prog(data, "Allocation error", "Error");
// 			while(z < data->nbr_arg)
// 				data->command->arg[y][z++] = ft_strdup(data->command->lign[i++]);
// 		}
// 		i++;
// 		y++;
// 	}
// 	print_cmd(data);
// 	print_arg(data);
// }

void pars_pipe(t_data *data)
{
	int	i;
	int y;
	int z;

	i = 0;
	y = 0;
	utils_pars_pipe(data);
	while (data->nbr_pipe-- >= 0)
	{
		z = 0;
		data->command->cmd[y] = ft_strdup(data->command->lign[i++]);
		if (data->command->lign[i] && *data->command->lign[i] == '|')
		{
			data->command->arg[y] = ft_calloc(1, sizeof(char *));
			if (!data->command->arg[y])
				ft_error_prog(data, "Allocation error", "Error");
			data->command->arg[y][0] = NULL;
			i++;
			y++;
			continue;
		}
		while (data->command->lign[i] && *data->command->lign[i] != '|')
		{
			count_args(data, i);
			data->command->arg[y] = ft_calloc(data->nbr_arg + 1, sizeof(char *));
			if (!data->command->arg[y])
				ft_error_prog(data, "Allocation error", "Error");
			while(z < data->nbr_arg)
				data->command->arg[y][z++] = ft_strdup(data->command->lign[i++]);
		}
		i++;
		y++;
	}

}
