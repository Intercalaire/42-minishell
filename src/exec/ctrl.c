/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:05:46 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/22 07:54:16 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include "../../include/parsing/minishell.h"


static void	handler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = signum;
}

static void	sigquit_handler(int signum)
{
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig = signum;
}

void	ft_sig(t_data *data)
{
	signal(SIGINT, handler);
	if (data->sig_status == 0)
		signal(SIGQUIT, SIG_IGN);
	else
	{
		signal(SIGQUIT, sigquit_handler);
		data->sig_status = 0;
	}
	if (g_sig)
	{
		if (g_sig == SIGQUIT)
			data->sig_status = 131;
		if (g_sig == SIGINT)
			data->sig_status = 130;
		g_sig = 0;
	}
}
