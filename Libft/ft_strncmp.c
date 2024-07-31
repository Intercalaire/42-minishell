/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:58:29 by vgodart           #+#    #+#             */
/*   Updated: 2023/10/31 16:08:04 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n )
{
	size_t			i;
	unsigned char	*new_s1;
	unsigned char	*new_s2;

	if (!s1 || !s2)
		return (1);
	i = 0;
	new_s1 = (unsigned char *) s1;
	new_s2 = (unsigned char *) s2;
	while (n != 0 && (new_s1[i] || new_s2[i]) != '\0')
	{
		if (new_s1[i] != new_s2[i])
			return (new_s1[i] - new_s2[i]);
		i++;
		n--;
	}
	return (0);
}
