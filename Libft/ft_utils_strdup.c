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

static int is_quote(char c);
static void handle_char(char *result, char *str, int *i, int *j, char *quote);

static int is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static void handle_char(char *result, char *str, int *i, int *j, char *quote)
{
	if (str[*i] == '\\' && (str[*i+1] == '\'' || str[*i+1] == '\"') && *quote == '\"')
	{
		result[(*j)++] = str[++(*i)];
	}
	else if (is_quote(str[*i]) && *quote == 0)
	{
		*quote = str[*i];
	}
	else if (str[*i] == *quote)
	{
		*quote = 0;
	}
	else
	{
		result[(*j)++] = str[*i];
	}
}

char *ft_trim_quote(char *str)
{
    int i = 0;
    int j = 0;
    char quote = 0;
    char *result;

	result = ft_calloc((ft_strlen(str) + 1), sizeof(char));
    if (result == NULL || str == NULL)
        return (NULL);
    while (str[i])
    {
        handle_char(result, str, &i, &j, &quote);
        i++;
    }

    result[j] = '\0';

    return (result);
}