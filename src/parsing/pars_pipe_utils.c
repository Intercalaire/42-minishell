/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:14:56 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/28 12:14:58 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static int	initialize_and_check_conditions(t_data *data, int *i, int *y);
static int	handle_command_arg(t_data *data, int *i, int *y, int *z);
static int	parse_command(t_data *data, int *i, int *y, int *z);

static int	initialize_and_check_conditions(t_data *data, int *i, int *y)
{
	count_args(data, *i);
	if (count_all(data, y, *i) == 2)
		return (2);
	return (0);
}

static int	handle_command_arg(t_data *data, int *i, int *y, int *z)
{
	char	*tmp;

	tmp = NULL;
	if (!data->command->cmd[*y])
	{
		tmp = ft_strdup_2(data, data->command->lign[(*i)]);
		if (ft_strlen(tmp) == 0)
		{
			free(tmp);
			return (0);
		}
		data->command->cmd[*y] = tmp;
		if (!data->command->cmd[*y])
			return (2);
	}
	else
	{
		data->command->arg[*y][*z]
			= ft_strdup_2(data, data->command->lign[(*i)]);
		if (!data->command->arg[*y][*z])
			return (2);
		(*z)++;
	}
	return (0);
}

static int	parse_command(t_data *data, int *i, int *y, int *z)
{
	if (data->command->lign[(*i)] && data->command->lign[(*i) + 1])
	{
		if (verif_lign(data, data->command->lign[(*i)]) == 0)
		{
			(*i)++;
			verif_output(data, y, data->command->lign[(*i)]);
		}
		else
		{
			if (handle_command_arg(data, i, y, z) == 2)
				return (2);
		}
	}
	else
	{
		if (handle_command_arg(data, i, y, z) == 2)
			return (2);
	}
	return (0);
}

int	handle_args(t_data *data, int *i, int *y, int *z)
{
	if (initialize_and_check_conditions(data, i, y) == 2)
		return (2);
	while (data->command->lign[(*i)] && *data->command->lign[(*i)] != '|')
	{
		if (parse_command(data, i, y, z) == 2)
			return (2);
		(*i)++;
	}
	if (data->command->cmd[0] == NULL && !data->output)
		return (2);
	return (0);
}
