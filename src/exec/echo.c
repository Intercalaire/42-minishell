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

int echo(t_data *data)
{
    int i;
    int newline = 1;

    i = 0;
    if (data->command->arg[i] && ft_strncmp(data->command->arg[i], "-n", 2) == 0)
    {
        newline = 0;
        i++;
    }
    while (data->command->arg[i])
    {
        printf("%s ", data->command->arg[i]);
        i++;
    }
    if (newline)
        printf("\n");
    return (0);
}