/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:09:36 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/08 14:09:38 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	countdigit(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

static	int	signsign(int nbr)
{
	int	sign;

	sign = 0;
	if (nbr < 0)
		sign = 1;
	return (sign);
}

static	char	*character_creator(char *str, int n, int sign, int i)
{
	while (i != 0)
	{
		str[i + sign - 1] = (n % 10) + '0';
		n = (n / 10);
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = countdigit(n);
	sign = signsign(n);
	str = malloc(sizeof(char ) * (sign + i + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	str[i + sign] = '\0';
	if (n == 0)
		str[0] = '0';
	str = character_creator(str, n, sign, i);
	return (str);
}
