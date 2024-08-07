/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_more_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 01:22:27 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/08 01:22:30 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

int	ft_export(t_data *data, char **arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
	{
		print_declare(data, i);
		return (0);
	}
	while (arg[i])
	{
		if (check_export(arg[i]))
			return (1);
		if (!ft_strchr(arg[i], '=') && search_env(data, arg[i]) == -1)
			add_env(data, arg[i], NULL);
		else if (ft_strnstr(arg[i], "+=", ft_strlen(arg[i])) != NULL)
			plus_equal(data, arg[i]);
		else if (ft_strchr(arg[i], '='))
			equal_sign(data, arg[i]);
		i++;
	}
	return (0);
}
