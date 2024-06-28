/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:16:19 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/30 15:16:27 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

void	count_pipes_outside_quotes(t_data *data, const char *str)
{
	int	in_single_quotes;
	int	in_double_quotes;
	int	i;

	data->nbr_pipe = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '|' && !in_single_quotes && !in_double_quotes)
			data->nbr_pipe++;
		i++;
	}
}

int	init_zero(t_data *data)
{
	data->meter->count_outfile = 0;
	data->meter->count_h_doc = 0;
	data->meter->count_infile = 0;
	data->meter->count_outfile_append = 0;
	return (0);
}

void	remove_end_space(char *str)
{
	int	len;

	if (str == NULL)
	{
		return ;
	}
	len = ft_strlen(str);
	while (len > 0 && str[len - 1] == ' ')
	{
		str[len - 1] = '\0';
		len--;
	}
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
