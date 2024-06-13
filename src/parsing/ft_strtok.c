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
static char	*adjust_pointers(char **src, char *next_token, char *s);

static char	*find_next_token(char *src, const char *delim)
{
	char	*p;
	int		in_quotes;

	in_quotes = 0;
	p = src;
	while (*p != '\0')
	{
		if (*p == '"' || *p == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && ft_strchr(delim, *p))
			break ;
		p++;
	}
	return (p);
}

static char	*adjust_pointers(char **src, char *next_token, char *s)
{
	char quote = 0;  // variable to hold the quote character

	if (*next_token != '\0')
	{
		if (*next_token == '"' || *next_token == '\'')
		{
			quote = *next_token;  // save the quote character
			s = ++(*src);  // start the token after the quote
			while (**src != quote && **src != '\0')  // find the matching quote
				(*src)++;
			*next_token = '\0';  // end the token before the matching quote
			if (**src != '\0')
				(*src)++;  // skip the matching quote
		}
		else
		{
			*next_token = '\0';
			s = *src;
			*src = ++next_token;
		}
	}
	else if (**src != '\0')
	{
		s = *src;
		*src = NULL;
	}
	return (s);
}

char	*ft_strtok(t_data *data, char *str, const char *delim)
{
	static char	*src = NULL;
	char		*next_token;
	char		*ret;
	char		*s;

	ret = 0;
	s = NULL;
	if (str != NULL)
		src = str;
	if (src == NULL)
		return (NULL);
	while (ft_strchr(delim, *src) && *src != '\0')
		src++;
	next_token = find_next_token(src, delim);
	ret = adjust_pointers(&src, next_token, s);
	ret = ft_split_delim(data, ret); 
	return (ret);
}
