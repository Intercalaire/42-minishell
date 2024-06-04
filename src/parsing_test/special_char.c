/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:23:41 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/03 18:23:43 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec_test/minishell.h"

int	special_char(t_data *data, char *str)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && in_quote == 1)
			in_quote = 0;
		if ((str[i] == '\'' || str[i] == '"') && in_quote == 0)
			in_quote = 1;
		if ((str[i] == ';' || str[i] == '\\'
				|| str[i] == '&' || str[i] == '*') && in_quote == 0)
		{
			ft_little_error_prog(data, str, TOKEN);
			return (1);
		}
		i++;
	}
	return (0);
}
