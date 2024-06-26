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

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*str;
	(void)argc;
	(void)argv;

	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	cpy_env(data, env);
	data->exit_status = 0;
	while (1)
	{
		init_data(data);
		ft_sig(data);
		str = readline("Minishell >");
		if (!str)
			exit_shell(data, str, NULL);
		if (ft_strlen(str) == 0)
		{
			ft_little_error_prog_no_msg(data, str);
			continue ;
		}
		add_history(str);
		remove_end_space(str);
		if (quote_verif(data, str) == 1 || special_char(data, str) == 1
			|| look_pipe(data, str) == 1)
		{
			data->exit_status = 2;
			continue ;
		}
		if (try_ft_strtok(data, str) == 2)
		{
			data->exit_status = 2;
			ft_error_prog(data, str, "Error");
			continue ;
		}
		if (pars_pipe(data) == 2)
		{
			data->exit_status = 2;
			ft_free_data(data, str);
			continue ;
		}
		my_pipe(data, str);
		ft_free_data(data, str);
	}
	ft_end_error_prog(data, str, "exit");
	return (0);
}
