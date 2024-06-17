/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:05:46 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/04 12:27:09 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ctrl C = SIGINT -> rl_on_new_line
//ctrl \ = SIGQUIT
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include "../../include/parsing/minishell.h"
static void handler(int signum)
{
	(void)signum;
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void quit_handler(int signum)
{
    (void)signum;
    rl_replace_line("", 0);
    rl_redisplay();
    write(1, "Minishell >", 11);
}

void ft_sig(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, quit_handler);
}

