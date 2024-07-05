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
static char	*adjust_pointers_with_quotes(char **src, char *next_token, char *s);
static char	*adjust_pointers_without_qts(char **src, char *next_token, char *s);
static char	*adjust_pointers(char **src, char *next_token, char *s);

char	*find_next_token(char *src, const char *delim)
{
	char	*next_token;
	int		in_quotes;
	int		in_single_quotes;

	next_token = src;
	in_quotes = 0;
	in_single_quotes = 0;
	while (*next_token != '\0')
	{
		if (*next_token == '"' && !in_single_quotes)
			in_quotes = !in_quotes;
		else if (*next_token == '\'' && !in_quotes)
			in_single_quotes = !in_single_quotes;
		if (!in_quotes && !in_single_quotes && ft_strchr(delim, *next_token))
			break ;
		next_token++;
	}
	return (next_token);
}

static char	*adjust_pointers_with_quotes(char **src, char *next_token, char *s)
{
	char	quote;

	quote = *next_token;
	s = ++(*src);
	while (**src != quote && **src != '\0')
		(*src)++;
	*next_token = '\0';
	if (**src != '\0')
		(*src)++;
	return (s);
}

static char	*adjust_pointers_without_qts(char **src, char *next_token, char *s)
{
	*next_token = '\0';
	s = *src;
	*src = ++next_token;
	return (s);
}

static char	*adjust_pointers(char **src, char *next_token, char *s)
{
	if (*next_token != '\0')
	{
		if (*next_token == '"' || *next_token == '\'')
			s = adjust_pointers_with_quotes(src, next_token, s);
		else
			s = adjust_pointers_without_qts(src, next_token, s);
	}
	else if (**src != '\0')
	{
		s = *src;
		*src = NULL;
	}
	return (s);
}

char	*ft_strtok(char *str, const char *delim)
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
	ret = ft_split_delim(ret);
	return (ret);
}
