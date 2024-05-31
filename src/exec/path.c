/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:18:09 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/10 12:12:20 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//dans les cas ou c'est different de echo, cd, pwd, export, unset, env, exit
int path(t_data *data)
{
	char *path;
	char **var;
	int bin;
	int i;

	i = 0;
	path = search_env(data, "PATH");
	printf("%s", path);
	var = ft_split(path, ":");
	while (var[i])
	{
		if (ft_strncmp(var[i], "/bin", 5) == 0)
			break ;
		i++;
	}
	if (!var[i])
		error("No /bin/");
	else
		bin = i;
	return (execve(data->command->cmd, data->command->arg, var));
	//argv = commande + arguments

}

int main(void)
{
	path();
	return 0;
}
