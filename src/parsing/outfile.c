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

void	outfile(t_data *data, char *str)
{
	int i;
	int j;
	int k;
	char *outfile;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && !(str[i] == '>'))
		i++;
	if (str[i] == '>')
	{
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i + j] && str[i + j] != ' ')
			j++;
		outfile = ft_calloc(j + 1, sizeof(char));
		while (k < j)
		{
			outfile[k] = str[i + k];
			k++;
		}
		outfile[k] = '\0';
		data->output->outfile[0] = ft_strdup(outfile);
		outfile_print(data);
	}
}

void outfile_append(t_data *data, char *str)
{
	int i;
	int j;
	int k;
	char *outfile;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && !(str[i] == '>' && str[i+1] == '>'))
		i++;
	if (str[i] == '>')
	{
		i += 2;
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i + j] && str[i + j] != ' ')
			j++;
		outfile = ft_calloc(j + 1, sizeof(char));
		while (k < j)
		{
			outfile[k] = str[i + k];
			k++;
		}
		outfile[k] = '\0';
		data->output->outfile_append[0] = ft_strdup(outfile);
		outfile_append_print(data);
	}
}

void	infile(t_data *data, char *str)
{
	int i;
	int j;
	int k;
	char *infile;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && !(str[i] == '<'))
		i++;
	if (str[i] == '<')
	{
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i + j] && str[i + j] != ' ')
			j++;
		infile = ft_calloc(j + 1, sizeof(char));
		while (k < j)
		{
			infile[k] = str[i + k];
			k++;
		}
		infile[k] = '\0';
		data->output->infile[0] = ft_strdup(infile);
		infile_print(data);
	}
}

void	h_doc(t_data *data, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(j < data->meter->count_h_doc)
	{
		data->output->h_doc[i][j] = ft_strdup(str);
		if (!data->output->h_doc[i][j])
			ft_error_prog(data, "Allocation error", "Error");
		j++;
	}

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

void verif_output(t_data *data, char *str)
{
	int i;

	i = 0;
	count_output(data, str);
	init_output(data);
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] != '>')
			outfile(data, str);
		if (str[i] == '>' && str[i + 1] == '>')
		{
			outfile_append(data, str);
			i++;
		}
		if (str[i] == '<' && str[i + 1] != '<')
			infile(data, str);
		if (str[i] == '<' && str[i + 1] == '<')
		{
				h_doc(data, str);
				i++;
		}
		i++;
	}
}

void	init_output(t_data *data)
{
	data->output->h_doc = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
	data->output->infile = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
	data->output->outfile = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
	data->output->outfile_append = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
	if (!data->output->h_doc || !data->output->infile || !data->output->outfile || !data->output->outfile_append)
		ft_error_prog(data, "Allocation error", "Error");
	data->output->outfile = ft_calloc(data->meter->count_outfile + 1, sizeof(char *));
	if (!data->output->outfile)
		ft_error_prog(data, "Allocation error", "Error");
	data->output->outfile_append = ft_calloc(data->meter->count_outfile_append + 1, sizeof(char *));
	if (!data->output->outfile_append)
		ft_error_prog(data, "Allocation error", "Error");
	data->output->infile = ft_calloc(data->meter->count_infile + 1, sizeof(char *));
	if (!data->output->infile)
		ft_error_prog(data, "Allocation error", "Error");
	data->output->h_doc = ft_calloc(data->meter->count_h_doc + 1, sizeof(char *));
	if (!data->output->h_doc)
		ft_error_prog(data, "Allocation error", "Error");
}
