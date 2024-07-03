/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 09:51:06 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/29 09:51:08 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

int	ktq_utils(int in_qte_dble, int in_qte_sple)
{
	if (in_qte_dble == 1)
		return (1);
	if (in_qte_sple == 1)
		return (3);
	return (0);
}
int	ft_isalnum_count(char *str)
{
	int	result;
	int	count;

	result = 0;
	count = 0;
	while (str[count])
		if ((str[count] >= 'a' && str[count] <= 'z') || (str[count] >= 'A' && str[count] <= 'Z')
		|| (str[count] >= '0' && str[count] <= '9'))
		result++;
	return (result);
}