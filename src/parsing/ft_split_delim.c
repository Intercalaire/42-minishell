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

static int	handle_special_chars(char *str, char *new_str, int i, int j);
static char	*init_new_str(char *new_str, char *str);
static int	process_char(char *str, char *new_str, int *i, int *j);

static int	handle_special_chars(char *str, char *new_str, int i, int j)
{
	if (i > 0 && str[i - 1] != ' ' && (str[i] == '>' || str[i] == '<'))
	{
		new_str[j++] = ' ';
	}
	new_str[j++] = str[i];
	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
				+ 1] == '<'))
	{
		new_str[j++] = str[++i];
	}
	if (str[i + 1] != '\0' && str[i + 1] != ' ' && (str[i] == '>'
			|| str[i] == '<'))
	{
		new_str[j++] = ' ';
	}
	return (j);
}

static char	*init_new_str(char *new_str, char *str)
{
	new_str = ft_calloc(ft_strlen(str) * 3 + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	*ft_split_delim(char *str)
{
	int		in_quotes;
	char	*new_str;
	int		j;
	int		i;

	new_str = NULL;
	new_str = init_new_str(new_str, str);
	if (!new_str || ft_strlen(str) == 0)
		return (NULL);
	init_int_values(&i, &j, &in_quotes);
	while (str[i] != '\0')
	{
		if ((str[i] == '|' || (str[i] == '>' || str[i] == '<'))
			&& know_the_delim_quote(str + i) > 2)
			j = process_char(str, new_str, &i, &j);
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

static int	process_char(char *str, char *new_str, int *i, int *j)
{
	if (*j > 0 && new_str[*j - 1] != ' ')
		new_str[(*j)++] = ' ';
	if (str[*i + 1] == str[*i])
	{
		*j = handle_special_chars(str, new_str, *i, *j);
		(*i)++;
	}
	else
		*j = handle_special_chars(str, new_str, *i, *j);
	new_str[(*j)++] = ' ';
	return (*j);
}
