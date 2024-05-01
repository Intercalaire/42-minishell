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

void ft_error(t_data *data, char *str)
{
	printf("%s\n", str);
	free(data);
	exit(EXIT_FAILURE);
}

int	main()
{
	t_data	*data;
	char	*str;

	data = malloc(sizeof(t_data));
	if (!data)
		return(EXIT_FAILURE);
	init_data(data);
	while (1)
	{
		str = readline("Minishell >");
		if (!str)
			break ;
		try_ft_strtok(data, str);
		add_history(str);
	}
	free(str);
	ft_error(data, "Error");
	return (0);
}
