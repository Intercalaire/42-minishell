/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:44:47 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/29 09:38:27 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static int	create_path(char *home, char *arg)
{
	char	*path;

	if (!arg)
		path = ft_strdup(home);
	else
	{
		if (ft_strncmp(arg, home, ft_strlen(home)) == 0)
			path = ft_strdup(arg);
		else
			path = ft_strjoin(home, arg + 1);
	}
	if (chdir(path) != 0)
	{
		print_error("Minishell: cd: ", path, ": No such file or directory");
		free(path);
		free(home);
		return (1);
	}
	free(path);
	return (0);
}

static int	directory_error(char *arg)
{
	if (chdir(arg) != 0)
	{
		if (errno == ENOENT)
			print_error("Minishell: cd: ", arg,
				": No such file or directory");
		else if (errno == EACCES || errno == EPERM)
			print_error("Minishell: cd: ", arg, ": Permission denied");
		else
			print_error("Minishell: cd: ", arg, ": Not a directory");
		return (1);
	}
	return (0);
}

static int	check_arg(char **arg, int k)
{
	if (arg && arg[1])
	{
		print_error("Minishell: cd: ", arg[0], ": Too many arguments");
		return (1);
	}
	if (k == -1 && !arg)
	{
		print_error("Minishell: cd: ", arg[0], ": HOME not set");
		return (1);
	}
	return (0);
}
static int do_cd(t_data *data, char *arg, char *home, char *oldpwd)
{
	if (arg == NULL || ft_strncmp(arg, "~", 1) == 0 || ft_strncmp(arg, home,
		ft_strlen(home)) == 0)
	{
		if (create_path(home, arg))
			return (1);
		env_update(data, oldpwd);
	}
	else
	{
		if (directory_error(arg))
			return (1);
		free(oldpwd);
	}
	return (0);
}

int	cd(t_data *data, char **arg)
{
	char	*oldpwd;
	char	*home;
	int		k;

	home = NULL;
	k = 0;
	k = search_env(data, "HOME");
	if (check_arg(arg, k))
		return (1);
	oldpwd = ft_calloc(PATH_MAX, sizeof(char));
	getcwd(oldpwd, PATH_MAX);
	if (k != -1)
		home = ft_strdup(data->env[k] + 5);
	if (do_cd(data, arg[0], home, oldpwd))
		return (1);
	free(home);
	return (0);
}
