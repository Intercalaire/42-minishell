/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:57:46 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/12 16:57:47 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static int	handle_quotes(char *str, char *new_str, int i, int j);
static int	handle_special_chars(char *str, char *new_str, int i, int j);

static int	handle_quotes(char *str, char *new_str, int i, int j)
{
	new_str[j++] = str[i];
	return (j);
}

static int	handle_special_chars(char *str, char *new_str, int i, int j)
{
	if (i > 0 && str[i - 1] != ' ' && new_str[j - 1] != ' ')
	{
		new_str[j++] = ' ';
	}
	new_str[j++] = str[i];
	if (str[i + 1] != '\0' && str[i + 1] != ' ' && new_str[j - 1] != ' ')
	{
		new_str[j++] = ' ';
	}
	return (j);
}

static char	*init_new_str(t_data *data, char *new_str, char  *str)
{
	new_str = ft_calloc(ft_strlen(str) * 3 + 1, sizeof(char));
	if (!new_str)
		ft_error_prog(data, NULL, "Error");
	return (new_str);
}

char	*ft_split_delim(t_data *data, char *str)
{
	int		in_quotes;
	char	*new_str;
	int		j;
	int		i;

	new_str = NULL;
	new_str = init_new_str(data ,new_str, str);
	in_quotes = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			in_quotes = !in_quotes;
			j = handle_quotes(str, new_str, i, j);
		}
		else if ((str[i] == '|' || str[i] == '>') && !in_quotes)
			j = handle_special_chars(str, new_str, i, j);
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
