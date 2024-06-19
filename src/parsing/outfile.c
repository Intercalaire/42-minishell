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
	int i;

	i = 0;
	while (data->output->outfile[i])
	{
		printf("outfile[%d] = %s\n", i, data->output->outfile[i]);
		i++;
	}
}

void h_doc_print(t_data *data)
{
	int i;

	i = 0;
	while (data->output->h_doc[i])
	{
		printf("h_doc[%d] = %s\n", i, data->output->h_doc[i]);
		i++;
	}
}

void outfile_append_print(t_data *data)
{
	int i;

	i = 0;
	while (data->output->outfile_append[i])
	{
		printf("outfile_append[%d] = %s\n", i, data->output->outfile_append[i]);
		i++;
	}
}

void infile_print(t_data *data)
{
	int i;

	i = 0;
	while (data->output->infile[i])
	{
		printf("infile[%d] = %s\n", i, data->output->infile[i]);
		i++;
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
		data->output->outfile = ft_calloc(2, sizeof(char *));
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
		data->output->outfile_append = ft_calloc(2, sizeof(char *));
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
		data->output->infile = ft_calloc(2, sizeof(char *));
		data->output->infile[0] = ft_strdup(infile);
		infile_print(data);
	}
}

void	h_doc(t_data *data, char *str)
{
	int i;
	int j;
	int k;
	char *h_doc;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && !(str[i] == '<' && str[i+1] == '<'))
		i++;
	if (str[i] == '<')
	{
		i += 2;
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i + j] && str[i + j] != ' ')
			j++;
		h_doc = ft_calloc(j + 1, sizeof(char));
		while (k < j)
		{
			h_doc[k] = str[i + k];
			k++;
		}
		h_doc[k] = '\0';
		data->output->h_doc = ft_calloc(2, sizeof(char *));
		data->output->h_doc[0] = ft_strdup(h_doc);
		h_doc_print(data);
	}
}

void verif_output(t_data *data, char *str)
{
	int i;

	i = 0;
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