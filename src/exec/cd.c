/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:44:47 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/29 10:08:59 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int absolute()
{
	chdir(data->command->arg[i][j]);

}

int relative()
{

}

void cd(t_data *data, int i, int j)
{
	int k;

	k = search_env(data, "HOME");
	if (k = -1)
		exit_error("no home found");
	if (ft_strncmp(data->command->arg[i][j], data->env[k], ft_strlen(data->env[k] == 0)
		absolute();
	else
		relative();







	char *str;
	str = ft_substr(s->pwd, "/");
	str = ft_substr(s->pwd, arg);
	if (chdir(str) == -1)
		error("Error");
}
