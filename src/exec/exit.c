/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 08:46:17 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/15 08:46:19 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"
void exit_shell(t_data *data, char *str)
{
    ft_free_data(data, str);
    //ft_end_error_prog(data, str, "exit");
    printf("exit\n");
    exit(0);
}
