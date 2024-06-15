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

#include "../../include/parsing/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

//dans les cas ou c'est different de echo, cd, pwd, export, unset, env, exit
int path(t_data *data, char *cmd, char **arg)
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
if (pid == 0)
{
    full_path = ft_strjoin(var[i], "/");
    full_path = ft_strjoin(full_path, cmd);
    char **args;
    if (arg == NULL) 
    {
        args = malloc(2 * sizeof(char *));
        args[0] = cmd;
        args[1] = NULL;
    } 
    else 
    {
        int arg_count = 0;
        while (arg[arg_count]) arg_count++; // count the number of arguments
        args = malloc((arg_count + 2) * sizeof(char *));
        args[0] = cmd;
        int j = 0;
        while (arg[j]) 
        {
            args[j + 1] = arg[j];
            j++;
        }
        args[j + 1] = NULL;
    }
        if (execve(full_path, args, data->env) == -1)
    {
        if (errno == ENOENT)
        {
            write(2, cmd, ft_strlen(cmd));
            write(2, ": command not found\n", 20);
        }
        else if (errno == EACCES)
        {
            write(2, cmd, ft_strlen(cmd));
            write(2, ": permission denied\n", 20);
        }
        else
        {
            write(2, cmd, ft_strlen(cmd));
            write(2, ": execution error\n", 18);
        }
        exit(EXIT_FAILURE);
    }
    free(args);
}
	else
		waitpid(pid, NULL, 0);
	return 0;
	//argv = commande + arguments

}
