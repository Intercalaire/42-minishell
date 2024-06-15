/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:13:40 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/04 11:13:42 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"


int echo(t_data *data, char **arg)
{
    (void)data;
    int i;
    int newline = 1;
    int j;

    j = 0;
    i = 0;
    if (!arg[i])
    {
        printf("\n");
        return (0);
    }
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
    while (arg[i])
    {
        printf("%s", arg[i]);
        if (arg[i + 1])
            printf(" ");
        i++;
    }
    if (newline == 1)
        printf("\n");
    return (0);
}