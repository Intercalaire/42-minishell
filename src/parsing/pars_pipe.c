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

static void	count_args(t_data *data, int i)
{
	data->nbr_arg = 0;
	while (data->command->lign[i] && *data->command->lign[i] != '|')
	{
		data->nbr_arg++;
		i++;
	}
}

static void	utils_pars_pipe(t_data *data)
{
	data->command->cmd = ft_calloc(data->nbr_pipe + 2, sizeof(char *));
	if (!data->command->cmd)
		ft_error_prog(data, "Allocation error", "Error");
	data->command->arg = ft_calloc(data->nbr_pipe + 2, sizeof(char **));
	if (!data->command->arg)
		ft_error_prog(data, "Allocation error", "Error");
}

static void	print_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->command->cmd[i])
	{
		printf("cmd[%d] : %s\n", i, data->command->cmd[i]);
		i++;
	}
}

static void	print_arg(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	if (data->command->arg != NULL)
	{
		while (data->command->arg[i])
		{
			y = 0;
			if (data->command->arg[i] != NULL)
			{
				while (data->command->arg[i][y])
				{
					printf("arg[%d][%d] : %s\n", i, y, data->command->arg[i][y]);
					y++;
				}
			}
			i++;
		}
	}
}

void	pars_pipe(t_data *data)
{
	int	i;
	int	y;
	int	z;

	i = 0;
	y = 0;
	utils_pars_pipe(data);
	while (data->nbr_pipe-- >= 0)
	{
		z = 0;
		data->command->cmd[y] = ft_strdup_2(data->command->lign[i++]);
		if (!data->command->cmd[y])
			ft_end_error_prog(data, "Allocation error", "Error");
		if (data->command->lign[i] && *data->command->lign[i] == '|')
		{
			data->command->arg[y] = ft_calloc(1, sizeof(char *));
			if (!data->command->arg[y])
				ft_error_prog(data, "Allocation error", "Error");
			data->command->arg[y][0] = NULL;
			i++;
			y++;
			continue ;
		}
		while (data->command->lign[i] && *data->command->lign[i] != '|')
		{
			count_args(data, i);
			data->command->arg[y] = ft_calloc(data->nbr_arg + 1, sizeof(char *));
			if (!data->command->arg[y])
				ft_error_prog(data, "Allocation error", "Error");
			while (z < data->nbr_arg)
			{
				data->command->arg[y][z++] = ft_strdup_2(data->command->lign[i++]);
				if (!data->command->arg[y][z - 1])
					ft_end_error_prog(data, "Allocation error", "Error");
			}
		}
		i++;
		y++;
	}
	print_cmd(data);
	print_arg(data);
}
// void process_commands(t_data *data, int *i, int *y)
// {
//     utils_pars_pipe(data);
//     while (data->nbr_pipe-- >= 0)
//     {
//         data->command->cmd[*y] = ft_strdup_2(data->command->lign[(*i)++]);
//         if (!data->command->cmd[*y])
//             ft_end_error_prog(data, "Allocation error", "Error");
//         if (data->command->lign[*i] && *data->command->lign[*i] == '|')
//         {
//             data->command->arg[*y] = ft_calloc(1, sizeof(char *));
//             if (!data->command->arg[*y])
//                 ft_error_prog(data, "Allocation error", "Error");
//             data->command->arg[*y][0] = NULL;
//             (*i)++;
//             (*y)++;
//         }
//     }
// }

// void process_arguments(t_data *data, int *i, int *y)
// {
// 	int z = 0;
// 	while (data->command->lign[*i] && *data->command->lign[*i] != '|')
// 	{
// 		count_args(data, *i);
// 		data->command->arg[*y] = ft_calloc(data->nbr_arg + 1, sizeof(char *));
// 		if (!data->command->arg[*y])
// 			ft_error_prog(data, "Allocation error", "Error");
// 		while(z < data->nbr_arg)
// 		{
// 			data->command->arg[*y][z] = ft_strdup_2(data->command->lign[(*i)++]);
// 			if (!data->command->arg[*y][z])
// 				ft_end_error_prog(data, "Allocation error", "Error");
// 			z++;
// 			if (z >= data->nbr_arg) {
// 				printf("Trying to access beyond allocated memory\n");
// 				exit(1);
// 			}
// 		}
// 		(*i)++;
// 		(*y)++;
// 	}
// }

// void pars_pipe(t_data *data)
// {
//     int i = 0;
//     int y = 0;

//     process_commands(data, &i, &y);
//     process_arguments(data, &i, &y);

//     print_cmd(data);
//     print_arg(data);
// }