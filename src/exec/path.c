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

void ft_free_path(char **path, char *var, char **args)
{
    ft_free_strtab(path);
    ft_free_strtab(args);
    if (var)
        free(var);

}

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
    {
        ft_free_strtab(var);
        return (1);
    }
if (pid == 0)
{
    if (ft_strncmp(cmd, "./", 2) == 0)
    {
        full_path = strdup(cmd);
    } 
    else 
    {
        full_path = ft_strjoin(var[i], "/");
        full_path = ft_strjoin(full_path, cmd);
    }
    char **args;
    if (arg == NULL) 
    {
        args = ft_calloc(2, sizeof(char *));
        args[0] = ft_strdup(cmd);
    } 
    else 
    {
        int arg_count = 0;
        while (arg[arg_count]) arg_count++; // count the number of arguments
        args = ft_calloc((arg_count + 2), sizeof(char *));
        args[0] = ft_strdup(cmd);
        int j = 0;
        while (arg[j + 1]) 
        {
            args[j + 1] = ft_strdup(arg[j]);
            j++;
        }
    }
        if (execve(full_path, args, data->env) == -1)
    {
        if (errno == ENOENT)
        {
            printf("%s: command not found\n", cmd);
            exit(127);
        }
        else if (errno == EACCES)
        {
            perror(cmd);
            exit (1);
        }
        else
        {
            perror(cmd);
            exit(127);
        }
    free(args);
    }
}
	else
    {
        ft_free_strtab(var);
		waitpid(pid, NULL, 0);
    }
	return 0;
	//argv = commande + arguments

}

