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

static int	outfile(t_data *data, int *y, int *z, char *str)
{
    
	int len;

	data->output->outfile[*y] = ft_calloc(data->meter->nbr_arg + 1, sizeof(char *));
	if (!data->output->outfile)
		ft_error_prog(data, "Allocation error", "Error");
	len = data->nbr_arg;
    while (*z < len - 1)
    {
        data->output->outfile[*y][*z] = ft_strdup_2(data, str);
        if (!data->output->outfile[*y][*z])
        {
            ft_free_data_no_str(data);
            return (2);
        }
        z++;
    }
	outfile_print(data);
    return (0);
}

static int outfile_append(t_data *data, int *y, int *z, char *str)
{
    
	int len;

	data->output->outfile_append[*y] = ft_calloc(data->meter->nbr_arg + 1, sizeof(char *));
	if (!data->output->outfile_append)
		ft_error_prog(data, "Allocation error", "Error");
	len = data->nbr_arg;
    while (*z < len - 1)
    {
        data->output->outfile_append[*y][*z] = ft_strdup_2(data, str);
        if (!data->output->outfile_append[*y][*z])
        {
            ft_free_data_no_str(data);
            return (2);
        }
        z++;
    }
	outfile_append_print(data);
    return (0);
}

static int	infile(t_data *data, int *y, int *z, char *str)
{
    
	int len;

	data->output->infile[*y] = ft_calloc(data->meter->nbr_arg + 1, sizeof(char *));
	if (!data->output->infile)
		ft_error_prog(data, "Allocation error", "Error");
	len = data->nbr_arg;
    while (*z < len - 1)
    {
        data->output->infile[*y][*z] = ft_strdup_2(data, str);
        if (!data->output->infile[*y][*z])
        {
            ft_free_data_no_str(data);
            return (2);
        }
        z++;
    }
	infile_print(data);
    return (0);
}

static int	h_doc(t_data *data, int *y, int *z, char *str)
{
    
	int len;

	data->output->h_doc[*y] = ft_calloc(data->meter->nbr_arg + 1, sizeof(char *));
	if (!data->output->h_doc)
		ft_error_prog(data, "Allocation error", "Error");
	len = data->nbr_arg;
    while (*z < len - 1)
    {
        data->output->h_doc[*y][*z] = ft_strdup_2(data, str);
        if (!data->output->h_doc[*y][*z])
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
	printf("nbr_pipe : %d\n", data->meter->nbr_pipe);
	data->output->h_doc = ft_calloc(data->meter->nbr_pipe + 2, sizeof(char **));
	data->output->infile = ft_calloc(data->meter->nbr_pipe + 2, sizeof(char **));
	data->output->outfile = ft_calloc(data->meter->nbr_pipe + 2, sizeof(char **));
	data->output->outfile_append = ft_calloc(data->meter->nbr_pipe + 2, sizeof(char **));
	if (!data->output->h_doc || !data->output->infile || !data->output->outfile || !data->output->outfile_append)
		ft_error_prog(data, "Allocation error", "Error");
}

void count_output(t_data *data, char *str)
{
    int i;

    i = 0;
	data->meter->nbr_arg = 0;
    while (str[i])
    {
		data->meter->nbr_arg++;
		i++;
    }
}
int verif_lign(t_data *data, char *str)
{
	int i;

	if (!str)
		return (2);
	i = 0;
	data->output->sign = 0;
	printf("str : %s\n", str);
	while (str[i])
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
        i++;
    }
	return (0);
}

int verif_output(t_data *data, int *y, int *z, char *str)
{
	if (!str || data->output->sign == 0)
		return (2);
    count_output(data, str);
	init_global(data);
	if (data->output->sign == 1)
	{
		if (outfile(data, y, z, str) == 2)
			return (2);
	}
	else if (data->output->sign == 2)
	{
		if (outfile_append(data, y, z, str) == 2)
			return (2);
	}
	else if (data->output->sign == 3)
	{
		if (infile(data, y, z, str) == 2)
			return (2);
	}
	else if (data->output->sign == 4)
	{
		if (h_doc(data, y, z, str) == 2)
			return (2);
	}
	return (0);
}
