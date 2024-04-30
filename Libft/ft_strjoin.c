/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:39:24 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/03 14:40:57 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (src[i])
		i++;
	while (dest[j] != '\0')
		j++;
	while (i != 0)
	{
		dest[j] = src[k];
		i--;
		j++;
		k++;
	}
	dest[j] = '\0';
	return (dest);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char		*result;
	size_t		len;

	if (s2 == NULL || s1 == NULL)
	{
		result = malloc(sizeof(char));
		result[0] = 0;
		return (result);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	ft_strcpy(result, (char *) s1);
	ft_strcat(result, (char *) s2);
	return (result);
}
