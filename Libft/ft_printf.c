/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:54:54 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/20 11:32:18 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	known_the_sign(const char sign, va_list args)
{
	if (sign == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	if (sign == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	if (sign == 'p')
		return (ft_hexa_fd(va_arg(args, unsigned long), "0123456789abcdef", 1));
	if (sign == 'd')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (sign == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (sign == 'u')
		return (ft_base_fd(va_arg(args, unsigned), "0123456789", 1));
	if (sign == 'x')
		return (ft_base_fd(va_arg(args, unsigned), "0123456789abcdef", 1));
	if (sign == 'X')
		return (ft_base_fd(va_arg(args, unsigned), "0123456789ABCDEF", 1));
	if (sign == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *sign, ...)
{
	int		i;
	int		len;
	int		len_sign;
	va_list	args;

	i = 0;
	len = 0;
	len_sign = 0;
	va_start(args, sign);
	if (!sign)
		return (-1);
	while (sign[i])
	{
		if (sign[i] != '%')
		{
			len_sign++;
			ft_putchar_fd(sign[i], 1);
		}
		else
			len += known_the_sign(sign[++i], args);
		i++;
	}
	len = len + len_sign;
	va_end(args);
	return (len);
}
