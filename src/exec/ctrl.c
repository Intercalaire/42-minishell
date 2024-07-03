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
	printf("handler de base");
	g_sig = signum;
}

static void	path_handler(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("handler de cat");
	g_sig = signum;
}

static void	sigquit_handler(int signum)
{
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig = signum;
}

int	ft_sig(t_data *data)
{
	// printf("sig_status = %d\n", data->sig_status);
	if (data->sig_status == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
	}
	else
	{
		signal(SIGINT, path_handler);
		signal(SIGQUIT, sigquit_handler);
	}
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
