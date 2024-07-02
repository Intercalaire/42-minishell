/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:27:53 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/19 07:27:58 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static int	count_all_utils(t_data *data, int *y);

int	verif_output(t_data *data, int *y, char *str)
{
	if (!str || data->output->sign == 0)
		return (2);
	count_output(data, str, *y);
	if (data->output->sign == 1)
	{
		if (outfile(data, y, str) == 2)
			return (2);
	}
	else if (data->output->sign == 2)
	{
		if (outfile_append(data, y, str) == 2)
			return (2);
	}
	else if (data->output->sign == 3)
	{
		if (infile(data, y, str) == 2)
			return (2);
	}
	else if (data->output->sign == 4)
	{
		if (h_doc(data, y, str) == 2)
			return (2);
	}
	return (0);
}

int	count_all(t_data *data, int *y, int i)
{
	int	count_output_result;

	count_output_result = 0;
	while (data->command->lign[i] && *data->command->lign[i] != '|')
	{
		count_output_result = count_output(data, data->command->lign[i], *y);
		if (!count_output_result)
			i += 2;
		else
		{
			data->meter->nbr_arg++;
			i++;
		}
	}
	if (count_all_utils(data, y) == 2)
		return (2);
	return (0);
}

static int	count_all_utils(t_data *data, int *y)
{
	data->output->infile[*y]
		= ft_calloc(data->meter->nbr_infile + 1, sizeof(char *));
	if (!data->output->infile)
		return (2);
	data->output->h_doc[*y]
		= ft_calloc(data->meter->nbr_h_doc + 1, sizeof(char *));
	if (!data->output->h_doc)
		return (2);
	data->output->outfile_append[*y]
		= ft_calloc(data->meter->nbr_outfile_append + 1, sizeof(char *));
	if (!data->output->outfile_append)
		return (2);
	data->output->outfile[*y]
		= ft_calloc(data->meter->nbr_outfile + 1, sizeof(char *));
	if (!data->output->outfile)
		return (2);
	data->command->arg[*y]
		= ft_calloc(data->nbr_arg + 1, sizeof(char *));
	if (!data->command->arg)
		return (2);
	return (0);
}
