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
		if (ft_strlen(str) == 0)
			continue ;
		add_history(str);
		if (quote_verif(data, str) == 1 || special_char(data, str) == 1 || look_pipe(data, str) == 1)
			continue ;
		try_ft_strtok(data, str);
		ft_free_data(data, str);

	}
	ft_little_error_prog(data, str,"Error");
	return (0);
}
