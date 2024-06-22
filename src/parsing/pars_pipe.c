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

static void	count_args(t_data *data, int i);
static void	utils_pars_pipe(t_data *data);
static void	handle_pipe(t_data *data, int *i, int *y);
static int	handle_args(t_data *data, int *i, int *y, int *z);

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
	init_global(data);
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

static void	handle_pipe(t_data *data, int *i, int *y)
{
	data->command->arg[*y] = ft_calloc(1, sizeof(char *));
	if (!data->command->arg[*y])
		ft_error_prog(data, "Allocation error", "Error");
	data->command->arg[*y][0] = NULL;
	(*i)++;
	(*y)++;
}

static int	handle_args(t_data *data, int *i, int *y, int *z)
{
	count_args(data, *i);
	count_all(data, y);

	while (*z < data->nbr_arg)
	{
		if (data->command->lign[(*i) + 1] && verif_lign(data, data->command->lign[(*i)]) == 0)
			verif_output(data, y, data->command->lign[(*i) + 1]);
		else
		{
			data->command->arg[*y][*z] = ft_strdup_2(data, data->command->lign[(*i)]);
			if (!data->command->arg[*y][*z])
			{
				ft_free_data_no_str(data);
				return (2);
			}
		(*z)++;
		}
		(*i)++;
	}
	return (0);
}

int	pars_pipe(t_data *data)
{
	int	i;
	int	y;
	int	z;

	i = 0;
	y = 0;
	data->meter->nbr_pipe = data->nbr_pipe;
	utils_pars_pipe(data);
	while (data->nbr_pipe-- >= 0)
	{
		z = 0;
		data->meter->count_outfile = 0;
		data->meter->count_h_doc = 0;
		data->meter->count_infile = 0;
		data->meter->count_outfile_append = 0;
		data->command->cmd[y] = ft_strdup_2(data, data->command->lign[i++]);
		if (!data->command->cmd[y])
		{
			ft_free_data_no_str(data);
			return (2);
		}
		if (data->command->lign[i] && *data->command->lign[i] == '|')
		{
			handle_pipe(data, &i, &y);
			continue ;
		}
		while (data->command->lign[i] && *data->command->lign[i] != '|')
		{
			if (handle_args(data, &i, &y, &z) == 2)
				return (2);
		}
		i++;
		y++;
	}
	print_cmd(data);
	print_arg(data);
	return (0);
}
