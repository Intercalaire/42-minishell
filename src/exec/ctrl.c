/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:05:46 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/30 14:39:39 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static void	handler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = signum;
}

static void	path_handler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig = signum;
}

static void	sigquit_handler(int signum)
{
	printf("Quit\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig = signum;
}

static int	manage_sig(t_data *data)
{
	if (g_sig)
	{
		if (g_sig == SIGQUIT)
			data->exit_status = 131;
		if (g_sig == SIGINT)
			data->exit_status = 130;
		g_sig = 0;
		return (1);
	}
	return (0);
}

int	ft_sig(t_data *data)
{
	if (data->sig_status == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
	}
	else if (data->sig_status == 1)
	{
		signal(SIGINT, path_handler);
		signal(SIGQUIT, sigquit_handler);
	}
	if (manage_sig(data))
		return (1);
	return (0);
}
