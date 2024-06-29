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
