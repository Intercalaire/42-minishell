/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:00:36 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/17 14:00:38 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static char	*find_next_token(char *src, const char *delim);
static char	*adjust_pointers(char **src, char *next_token);

static char	*find_next_token(char *src, const char *delim)
{
	char	*p;
	int     in_quotes = 0;

	p = src;
	while (*p != '\0') {
		if (*p == '"' || *p == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && ft_strchr(delim, *p))
			break;
		p++;
	}
	return (p);
}

static char	*adjust_pointers(char **src, char *next_token)
{
	char	*ret;

	ret = NULL;
	if (*next_token != '\0')
	{
		if (*next_token == '"' || *next_token == '\'') // Si le token est un guillemet
		{
			*next_token = 0;
			ret = *src;
			*src = ++next_token;
			while (**src != *next_token && **src != '\0') // Skip jusqu'au prochain guillemet correspondant ou la fin de la chaîne
				(*src)++;
			if (**src == *next_token) // Si nous avons trouvé un guillemet correspondant
				(*src)++; // Skip le guillemet
		}
		else // Si le token n'est pas un guillemet
		{
			*next_token = 0;
			ret = *src;
			*src = ++next_token;
		}
	}
	else if (**src != '\0')
	{
		ret = *src;
		*src = NULL;
	}
	return (ret);
}

char	*ft_strtok(t_data *data, char *str, const char *delim)
{
	static char	*src = NULL;
	char		*next_token;
	char		*ret;

	ret = 0;
	if (str != NULL)
		src = str;
	if (src == NULL)
		return (NULL);
	while (ft_strchr(delim, *src) && *src != '\0')
		src++;
	next_token = find_next_token(src, delim);
	ret = adjust_pointers(&src, next_token);
	ret = ft_split_delim(data, ret);
	return (ft_trim_quote(data, ret));
}
