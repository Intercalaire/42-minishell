/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:21:53 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/30 14:32:55 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

char	*var_path(t_data *data, char *cmd)
{
	int		path_index;
	char	**var;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	path_index = search_env(data, "PATH");
	if (path_index == -1)
	{
		printf("minishell: %s: No such file or directory\n", cmd);
		data->exit_status = 127;
		return (NULL);
	}
	var = ft_split(data->env[path_index] + 5, ':');
	while (var[i++])
	{
		if (!ft_strncmp(var[i], "/bin", 5))
			break ;
	}
	tmp = ft_strjoin(var[i], "/");
	ft_free_strtab(var);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

char	**create_args(char *cmd, char **arg)
{
	char	**args;
	int		arg_count;
	int		j;

	j = 0;
	arg_count = 0;
	if (arg)
		while (arg[arg_count])
			arg_count++;
	args = ft_calloc((arg_count + 2), sizeof(char *));
	args[0] = ft_strdup(cmd);
	if (arg)
	{
		while (arg[j])
		{
			args[j + 1] = ft_strdup(arg[j]);
			j++;
		}
	}
	return (args);
}

static void	error_manage(t_data *data, char *cmd, char **args)
{
	if (errno == ENOENT)
	{
		printf("%s: command not found\n", cmd);
		data->exit_status = 127;
		exit(127);
	}
	else if (errno == EACCES)
	{
		printf("%s: permission denied\n", cmd);
		data->exit_status = 126;
		exit(126);
	}
	else
	{
		perror(args[0]);
		data->exit_status = 1;
		exit(1);
	}
}

void	execution(t_data *data, char *cmd, char **args, char *full_path)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (execve(cmd, args, data->env) == -1)
		{
			perror(cmd);
			exit(127);
		}
	}
	else
	{
		if (execve(full_path, args, data->env) == -1)
			error_manage(data, cmd, args);
		else 
			data->exit_status = 0;
	}
}
