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

static int	utils_pars_pipe(t_data *data);
static void	handle_pipe(t_data *data, int *i, int *y);

void	count_args(t_data *data, int i)
{
	data->nbr_arg = 0;
	while (data->command->lign[i] && *data->command->lign[i] != '|')
	{
		data->nbr_arg++;
		i++;
	}
}

static int	utils_pars_pipe(t_data *data)
{
	data->command->cmd = ft_calloc(data->nbr_pipe + 2, sizeof(char *));
	if (!data->command->cmd)
		return (2);
	data->command->arg = ft_calloc(data->nbr_pipe + 2, sizeof(char **));
	if (!data->command->arg)
		return (2);
	data->output->here_d = ft_calloc(data->nbr_pipe + 2, sizeof(int));
	if (!data->output->here_d)
		return (2);
	data->output->append = ft_calloc(data->nbr_pipe + 2, sizeof(int));
	if (!data->output->append)
		return (2);
	init_global(data);
	return (0);
}

static void	handle_pipe(t_data *data, int *i, int *y)
{
	(void)data;
	(*i)++;
	(*y)++;
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
					printf("arg[%d][%d] : %s\n", i,
						y, data->command->arg[i][y]);
					y++;
				}
			}
			i++;
		}
	}
}

int	pars_pipe(t_data *data)
{
	int	i;
	int	y;
	int	z;

	i = 0;
	y = 0;
	if (utils_pars_pipe(data) == 2)
		return (2);
	while (data->nbr_pipe-- >= 0)
	{
		z = init_zero(data);
		while (data->command->lign[i] && *data->command->lign[i] != '|')
		{
			if (handle_args(data, &i, &y, &z) == 2)
				return (2);
		}
		if (data->command->lign[i] && *data->command->lign[i] == '|')
		{
			handle_pipe(data, &i, &y);
			continue ;
		}
		y++;
		i++;
	}
	print_cmd(data);
	print_arg(data);
	return (0);
}
