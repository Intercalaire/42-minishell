/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_strdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:32:43 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/12 13:32:45 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_quote(char c);
static void	handle_char(char *result, char *str, t_str_index *index);
static char	*ft_trim_quote_utils(char *result, int j, char *str);

static int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static void	handle_char(char *result, char *str, t_str_index *index)
{
	if (str && str[*(index->i)] && str[*(index->i)] == '\\'
		&& (str[*(index->i) + 1] == '\''
			|| str[*(index->i) + 1] == '\"') && *(index->quote) == '\"')
	{
		result[(*(index->j))++] = str[++(*(index->i))];
	}
	else if (str && str[*(index->i)]
		&& is_quote(str[*(index->i)]) && *(index->quote) == 0)
	{
		*(index->quote) = str[*(index->i)];
	}
	else if (str && str[*(index->i)] && str[*(index->i)] == *(index->quote))
	{
		*(index->quote) = 0;
	}
	else
	{
		result[(*(index->j))++] = str[*(index->i)];
	}
}

char	*ft_trim_quote(char *str)
{
	int			i;
	int			j;
	char		quote;
	char		*result;
	t_str_index	index;

	i = 0;
	j = 0;
	quote = 0;
	index.i = &i;
	index.j = &j;
	index.quote = &quote;
	result = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (result == NULL || str == NULL)
		return (NULL);
	while (str[i])
	{
		handle_char(result, str, &index);
		i++;
	}
	result = ft_trim_quote_utils(result, j, str);
	return (result);
}

static char	*ft_trim_quote_utils(char *result, int j, char *str)
{
	char		*tmp;

	tmp = ft_strdup(str);
	result[j] = '\0';
	free(str);
	str = NULL;
	if (ft_strlen(result) == 0 && ft_strlen(tmp) != 0)
	{
		free(result);
		result = ft_strdup(" ");
	}
	free(tmp);
	return (result);
}
