/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:13:40 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/22 08:19:49 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static void	print_args(char **arg, int i)
{
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
}

static int	check_arg(char **arg, int i)
{
	if (!arg || !arg[i])
	{
		printf("\n");
		return (0);
	}
	return (1);
}

int	echo(char **arg)
{
	int	i;
	int	j;
	int	newline;

	i = 0;
	newline = 1;
	j = 0;
	if (!check_arg(arg, i))
		return (0);
	while (arg[i] && ft_strncmp(arg[i], "-n", 2) == 0)
	{
		j = 2;
		while (arg[i][j] == 'n')
			j++;
		if (arg[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	print_args(arg, i);
	if (newline == 1)
		printf("\n");
	return (0);
}
