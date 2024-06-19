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
#include <limits.h>
int is_valid_number(char *str)
{
    int i = 0;

    // Handle negative numbers.
    if (str[i] == '-')
        i++;

    // Check for digits.
    while (str[i] != '\0')
    {
        if (!isdigit(str[i]))
            return 0;
        i++;
    }

    return 1;
}

static long long ft_atol(char *str)
{
    int i = 0;
    int sign = 1;
    long long result = 0;

    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10 && str[i] - '0' > LLONG_MAX % 10))
        {
            if (sign == 1)
            return LLONG_MAX;
            else
            return LLONG_MIN;
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (sign * result);
}

void exit_shell(t_data *data, char *str, char **arg)
{
    long long exit_code;
    if (!arg)
    {
        exit_code = data->exit_status;
    }
    else
    {
        if (is_valid_number(arg[0]))
        {
            exit_code = ft_atol(arg[0]);
            if (exit_code < LLONG_MIN || exit_code > LLONG_MAX)
            {
                printf("minishell: exit: %s: numeric argument required\n", arg[0]);
                exit_code = 2;
            }
            else
                exit_code = exit_code % 256;
        }
        else
        {
            printf("minishell: exit: %s: numeric argument required\n", arg[0]);
            exit_code = 2;
        }
    }

    ft_free_data(data, str);
    if (data->env)
        ft_free_strtab(data->env);
    if (data)
        free(data);
    rl_free_line_state();  // Free memory allocated by readline
    printf("exit\n");
    exit(exit_code);
}