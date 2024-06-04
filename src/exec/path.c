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

#include "../../include/exec_test/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

//dans les cas ou c'est different de echo, cd, pwd, export, unset, env, exit
int path(t_data *data)
{
	int path;
	char **var;
	int i;
	char *full_path;
	pid_t pid;

	pid = fork();
	i = 0;
	path = search_env(data, "PATH");
	var = ft_split(data->env[path] + 5, ':');
	while (var[i])
	{
		if (!ft_strncmp(var[i], "/bin", 5))
			break ;
		i++;
	}
	if (!var[i])
		return 0;
		//error("No /bin/");
	if (pid == 0)
{
	full_path = ft_strjoin(var[i], "/");
	full_path = ft_strjoin(full_path, data->command->cmd[0]);
	execve(full_path, data->command->arg[0], data->env);
}
	else
		waitpid(pid, NULL, 0);
	return 0;
	//argv = commande + arguments

}
