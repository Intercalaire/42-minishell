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

char	*var_path(t_data *data, char *cmd)
{
	int		path_index;
	char	**var;
	int		i;
	char	*path;

	i = 0;
	path_index = search_env(data, "PATH");
	if (path_index == -1)
	{
		print_error("Minishell: ", cmd, ": No such file or directory");
		data->exit_status = 127;
		return (NULL);
	}
	var = ft_split(data->env[path_index] + 5, ':');
	while (var[i])
	{
		if (!ft_strncmp(var[i], "/bin", 5))
			break ;
		i++;
	}
	path = do_path(cmd, var, i);
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

static void	error_utils(t_data *data, char *cmd, char **args, char *full_path)
{
	if (errno == EACCES)
	{
		print_error("Minishell: ", cmd, ": Permission denied");
		data->exit_status = 126;
		ft_end_error_prog(data);
		free_path(full_path, args);
		exit(126);
	}
	else
	{
		perror(args[0]);
		data->exit_status = 1;
		ft_end_error_prog(data);
		free_path(full_path, args);
		exit(1);
	}
}

static void	error_manage(t_data *data, char *cmd, char **args, char *full_path)
{
	if (ft_strncmp(cmd, "ls", 3) == 0)
	{
		printf("OOOOOOOH im not a ls");
		data->exit_status = 0;
		ft_end_error_prog(data);
		free_path(full_path, args);
		exit(0);
	}
	if (errno == ENOENT)
	{
		print_error("Minishell: ", cmd, ": Command not found");
		data->exit_status = 127;
		ft_end_error_prog(data);
		free_path(full_path, args);
		exit(127);
	}
	else
		error_utils(data, cmd, args, full_path);
}

void	execution(t_data *data, char *cmd, char **args, char *full_path)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		data->exit_status = 0;
		execve(cmd, args, data->env);
		error_manage(data, cmd, args, full_path);
	}
	else
	{
		data->exit_status = 0;
		execve(full_path, args, data->env);
		error_manage(data, cmd, args, full_path);
	}
}
