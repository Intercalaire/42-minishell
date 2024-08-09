/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 03:04:01 by hsolet            #+#    #+#             */
/*   Updated: 2024/08/09 03:04:06 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_sign(char *str, int *i, int *error)
{
	int	sign;

	sign = 1;
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	if (!str[*i])
		*error = 1;
	return (sign);
}

long long	check_min(int *error, int sign, unsigned long long result)
{
	if (*error)
	{
		if (sign == -1 && result == (unsigned long long)LLONG_MAX + 1)
		{
			*error = 0;
			return (LLONG_MIN);
		}
	}
	return (result);
}

long long	ft_atol(char *str, int *error)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	result = 0;
	sign = check_sign(str, &i, error);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && str[i]
					- '0' > LLONG_MAX % 10))
				*error = 1;
			result = result * 10 + (str[i] - '0');
			i++;
		}
		else
		{
			*error = 1;
			break ;
		}
	}
	result = check_min(error, sign, result);
	return (sign * result);
}
