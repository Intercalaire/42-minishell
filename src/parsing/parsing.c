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

int	main(void)
{
	t_data	*data;
	char	*str;

	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	while (1)
	{
		init_data(data);
		str = readline("Minishell >");
		if (!str)
			break ;
		remove_end_space(str);
		if (ft_strlen(str) == 0)
		{
			ft_little_error_prog_no_msg(data, str);
			continue ;
		}
		add_history(str);
		if (quote_verif(data, str) == 1 || special_char(data, str) == 1
			|| look_pipe(data, str) == 1)
			continue ;
		str = ft_trim_quote(str);
		if (try_ft_strtok(data, str) == 1)
			continue ;
		pars_pipe(data);
		ft_free_data(data, str);
	}
	ft_end_error_prog(data, str, "exit");
	return (0);
}
