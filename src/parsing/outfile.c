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

void outfile_print(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	if (data->output->outfile != NULL)
	{
		while (data->output->outfile[i])
		{
			y = 0;
			if (data->output->outfile[i] != NULL)
			{
				while (data->output->outfile[i][y])
				{
					printf("outfile[%d][%d] : %s\n", i, y, data->output->outfile[i][y]);
					y++;
				}
			}
			i++;
		}
	}
}

void h_doc_print(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	if (data->output->h_doc != NULL)
	{
		while (data->output->h_doc[i])
		{
			y = 0;
			if (data->output->h_doc[i] != NULL)
			{
				while (data->output->h_doc[i][y])
				{
					printf("h_doc[%d][%d] : %s\n", i, y, data->output->h_doc[i][y]);
					y++;
				}
			}
			i++;
		}
	}
}

void outfile_append_print(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	if (data->output->outfile_append != NULL)
	{
		while (data->output->outfile_append[i])
		{
			y = 0;
			if (data->output->outfile_append[i] != NULL)
			{
				while (data->output->outfile_append[i][y])
				{
					printf("outfile_append[%d][%d] : %s\n", i, y, data->output->outfile_append[i][y]);
					y++;
				}
			}
			i++;
		}
	}
}

void infile_print(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	if (data->output->infile != NULL)
	{
		while (data->output->infile[i])
		{
			y = 0;
			if (data->output->infile[i] != NULL)
			{
				while (data->output->infile[i][y])
				{
					printf("infile[%d][%d] : %s\n", i, y, data->output->infile[i][y]);
					y++;
				}
			}
			i++;
		}
	}
}

static int	outfile(t_data *data, int *y, char *str)
{
    int z;

    z = 0;
    while (z < data->nbr_arg)
    {
        data->output->outfile[*y][z] = ft_strdup_2(data, str);
        if (!data->output->outfile[*y][z])
        {
            ft_free_data_no_str(data);
            return (2);
        }
        z++;
    }
	outfile_print(data);
    return (0);
}

static int outfile_append(t_data *data, int *y, char *str)
{
    int z;

    z = data->meter->count_outfile_append;
    while (z < data->nbr_arg)
    {
        data->output->outfile_append[*y][z] = ft_strdup_2(data, str);
        if (!data->output->outfile_append[*y][z])
        {
            ft_free_data_no_str(data);
            return (2);
        }
        z++;
    }
	outfile_append_print(data);
    return (0);
}

static int	infile(t_data *data, int *y, char *str)
{
    int z;

    z = data->meter->count_infile;
    while (z < data->nbr_arg)
    {
        data->output->infile[*y][z] = ft_strdup_2(data, str);
        if (!data->output->infile[*y][z])
        {
            ft_free_data_no_str(data);
            return (2);
        }
        z++;
    }
	infile_print(data);
    return (0);
}

static int	h_doc(t_data *data, int *y, char *str)
{
    int z;

    z = data->meter->count_h_doc;
    while (z < data->nbr_arg)
    {
        data->output->h_doc[*y][z] = ft_strdup_2(data, str);
        if (!data->output->h_doc[*y][z])
        {
            ft_free_data_no_str(data);
            return (2);
        }
        z++;
    }
	h_doc_print(data);
    return (0);
}

void	init_global(t_data *data)
{
	data->output->h_doc = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
	data->output->infile = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
	data->output->outfile = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
	data->output->outfile_append = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
	if (!data->output->h_doc || !data->output->infile || !data->output->outfile || !data->output->outfile_append)
		ft_error_prog(data, "Allocation error", "Error");
}

void	init_output(t_data *data, int *y)
{
	data->output->outfile[*y] = ft_calloc(data->meter->count_outfile + 1, sizeof(char *));
	if (!data->output->outfile)
		ft_error_prog(data, "Allocation error", "Error");
	data->output->outfile_append[*y] = ft_calloc(data->meter->count_outfile_append + 1, sizeof(char *));
	if (!data->output->outfile_append)
		ft_error_prog(data, "Allocation error", "Error");
	data->output->infile[*y] = ft_calloc(data->meter->count_infile + 1, sizeof(char *));
	if (!data->output->infile)
		ft_error_prog(data, "Allocation error", "Error");
	data->output->h_doc[*y] = ft_calloc(data->meter->count_h_doc + 1, sizeof(char *));
	if (!data->output->h_doc)
		ft_error_prog(data, "Allocation error", "Error");
}

void count_output(t_data *data, char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
		if (str[i] == '>' && str[i + 1] != '>')
			data->meter->count_outfile++;
        if (str[i] == '>' && str[i + 1] == '>')
        {
            data->meter->count_outfile_append++;
            i++;
        }
        if (str[i] == '<' && str[i + 1] != '<')
            data->meter->count_infile++;
        if (str[i] == '<' && str[i + 1] == '<')
        {
        	data->meter->count_h_doc++;
            i++;
        }
        i++;
    }
}
int verif_lign(char *str)
{
	if (!str)
		return (2);
	printf("str : %s\n", str);
	if (str[0] == '>' || str[0] == '<')
		return (0);
	return (2);
}

int verif_output(t_data *data, int *y, char *str)
{
    int i;

    i = 0;
	if (!str)
		return (2);
	printf("strtg : %s\n", str);
	init_global(data);
    count_output(data, str);
    init_output(data, y);
    while (str[i])
    {
        if (str[i] == '>' && str[i + 1] != '>')
            outfile(data, y, str);
        if (str[i] == '>' && str[i + 1] == '>')
        {
            outfile_append(data, y, str);
            i++;
        }
        if (str[i] == '<' && str[i + 1] != '<')
            infile(data, y, str);
        if (str[i] == '<' && str[i + 1] == '<')
        {
                h_doc(data, y, str);
                i++;
        }
        i++;
    }
	return (0);
}
