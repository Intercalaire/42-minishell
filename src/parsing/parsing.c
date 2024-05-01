/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:34:47 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/30 14:34:48 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

int	main()
{
	// t_data	data;
	char	*str;

	//init_data(&data, argc);
	while (1)
	{
		str = readline("Minishell >");
		try_ft_strtok(str);
		add_history(str);
	}
	free(str);
	return (0);
}
