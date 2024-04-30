/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:19:01 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/20 12:19:03 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen2(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		size;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	size = ft_strlen2(s1) + ft_strlen2(s2);
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[size] = 0;
	return (ret);
}

char	*ft_strchr2(const char *str, int charac)
{
	if (!str)
		return (NULL);
	while (*str || (char)charac == '\0')
	{
		if (*str == (char)charac)
			return ((char *)str);
		str++;
	}
	if (*str == charac)
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlcpy2(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen2(src);
	if (!size)
		return (len);
	while (++i < size - 1 && src[i])
		dst[i] = src[i];
	dst[i] = 0;
	return (len);
}
