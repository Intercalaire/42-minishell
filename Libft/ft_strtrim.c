/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:18:38 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/05 12:18:41 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*s2;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[j]) && s1[j])
		j--;
	while (ft_strchr(set, s1[i]) && i <= j)
		i++;
	s2 = malloc(sizeof(char) * (j - i + 2));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, &s1[i], j - i + 2);
	return (s2);
}
