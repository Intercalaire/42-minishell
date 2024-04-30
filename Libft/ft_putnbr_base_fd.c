/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:58:45 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/14 16:58:59 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_len(unsigned int n, char *base)
{
	int	len;

	len = 0;
	while (n >= ft_strlen(base))
	{
		len++;
		n = n / ft_strlen(base);
	}
	return (len + 1);
}

static void	ft_putnbr_base_write(unsigned int n, char *base, int fd)
{
	if (n >= ft_strlen(base))
		ft_putnbr_base_write(n / ft_strlen(base), base, fd);
	ft_putchar_fd(base[n % ft_strlen(base)], fd);
}

int	ft_base_fd(unsigned int n, char *base, int fd)
{
	ft_putnbr_base_write(n, base, fd);
	return (ft_count_len(n, base));
}
