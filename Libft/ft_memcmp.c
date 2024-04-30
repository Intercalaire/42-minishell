/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:57:00 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/02 11:31:26 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr2;

	i = 0;
	ptr = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	if (n == 0)
		return (n);
	while (i < n)
	{
		if ((ptr[i] != ptr2[i]))
			return (ptr[i] - ptr2[i]);
		i++;
	}
	return (0);
}
