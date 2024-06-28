/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:51:06 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/25 10:51:08 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static int	count_output_utils(t_data *data, char *str, int y, int i);
static int	verif_lign_utils(t_data *data, char *str, int i);

int	count_output(t_data *data, char *str, int y)
{
	int	i;

	i = 0;
	if (str[i] == '>' && str[i + 1] != '>')
	{
		data->meter->nbr_outfile += 1;
		data->output->append[y] = 0;
	}
	else if (str[i + 1] && str[i] == '>' && str[i + 1] == '>')
	{
		data->meter->nbr_outfile_append += 1;
		data->output->append[y] = 1;
	}
	else if (count_output_utils(data, str, y, i) == 1)
		return (1);
	return (0);
}

static int	count_output_utils(t_data *data, char *str, int y, int i)
{
	if (str[i] == '<' && str[i + 1] != '<')
	{
		data->meter->nbr_infile += 1;
		data->output->here_d[y] = 0;
	}
	else if (str[i + 1] && str[i] == '<' && str[i + 1] == '<')
	{
		data->meter->nbr_h_doc += 1;
		data->output->here_d[y] = 1;
	}
	else
		return (1);
	return (0);
}

static int	verif_lign_utils(t_data *data, char *str, int i)
{
	if (str[i] == '\"' || str[i] == '\'')
	{
		if (data->in_quote == 0)
			data->in_quote = 1;
		else
			data->in_quote = 0;
	}
	if (data->in_quote == 0)
	{
		if (str[i] == '>' && str[i + 1] != '>')
			data->output->sign = 1;
		if (str[i] == '>' && str[i + 1] == '>')
		{
			data->output->sign = 2;
			i++;
		}
		if (str[i] == '<' && str[i + 1] != '<')
			data->output->sign = 3;
		if (str[i] == '<' && str[i + 1] == '<')
		{
			data->output->sign = 4;
			i++;
		}
	}
	return (i);
}

int	verif_lign(t_data *data, char *str)
{
	int	i;

	if (!str)
		return (2);
	i = 0;
	data->in_quote = 0;
	data->output->sign = 0;
	while (str[i])
	{
		i = verif_lign_utils(data, str, i);
		i++;
	}
	if (data->output->sign == 0)
		return (2);
	return (0);
}
