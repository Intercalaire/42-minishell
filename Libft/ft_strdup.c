/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:26:27 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/03 14:26:30 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_trim_quote(char *str);
static char *ft_utils_trim_quote(char *str, int j, char *ret, char quote);

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	str = ft_calloc((i + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i != 0)
	{
		str[j] = s[j];
		i--;
		j++;
	}
	return (str);
}

char	*ft_strdup_2(const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	str = ft_calloc((i + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i != 0)
	{
		str[j] = s[j];
		i--;
		j++;
	}
	return (ft_trim_quote(str));
}

static char	*ft_trim_quote(char *str)
{
    int	i;
    int	j;
    int	len;
    char	*ret;
    char	quote;

    i = 0;
    j = 0;
    quote = 0;
    len = ft_strlen(str);
	if (!str)
		return (NULL);
    ret = malloc(sizeof(char) * (len + 1));
    while (str[i] && !quote)
    {
        if (str[i] == '"' || str[i] == '\'')
            quote = str[i];
        i++;
    }
	return (ft_utils_trim_quote(str, j, ret, quote));
}

static char *ft_utils_trim_quote(char *str, int j, char *ret, char quote)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != quote)
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
