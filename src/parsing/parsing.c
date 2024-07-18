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
		ft_sig(data);
		if (!str)
			exit_shell(data, NULL);
		if (ft_strlen(str) == 0)
		{
			ft_little_error_prog_no_msg(data, str);
			continue ;
		}
		add_history(str);
		if (remove_end_space(data, str) == 2)
			continue ;
		if (quote_verif(data, str) == 1 || special_char(data, str) == 1
			|| look_pipe(data, str) == 1 || look_out(data, str) == 1)
		{
			data->exit_status = 2;
			continue ;
		}
		if (try_ft_strtok(data, str) == 2)
		{
			data->exit_status = 2;
			ft_free_data(data, str);
			continue ;
		}
		if (data->size == 0)
		{
			ft_free_data(data, str);
			continue ;
		}
		if (pars_pipe(data) == 2)
		{
			data->exit_status = 2;
			ft_free_data(data, str);
			continue ;
		}
		free(str);
		my_pipe(data);
		ft_sig(data);
		str = NULL;
		ft_free_data(data, str);
	}
	ft_end_error_prog(data);
	return (0);
}
