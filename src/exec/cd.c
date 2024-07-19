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
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/parsing/minishell.h"
#include <limits.h>
#include <errno.h>

static void	env_update(t_data *data, char *oldpwd)
{
	char	*newpwd;

	newpwd = ft_calloc(PATH_MAX, sizeof(char));
	getcwd(newpwd, PATH_MAX);
	if (search_env(data, "OLDPWD") == -1)
		add_env(data, "OLDPWD", oldpwd);
	else
		change_env(data, "OLDPWD", oldpwd);
	if (search_env(data, "PWD") == -1)
		add_env(data, "PWD", newpwd);
	else
		change_env(data, "PWD", newpwd);
	free(newpwd);
	free(oldpwd);
}

static int	create_path(char *home, char **arg)
{
	char	*path;

	if (!arg || !arg[0])
		path = ft_strdup(home);
	else
	{
		if (ft_strncmp(arg[0], home, ft_strlen(home)) == 0)
			path = ft_strdup(arg[0]);
		else
			path = ft_strjoin(home, arg[0] + 1);
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

static int	directory_error(char **arg)
{

	if (chdir(arg[0]) != 0)
	{
		if (errno == ENOENT)
			print_error("Minishell: cd: ", arg[0], ": No such file or directory");
		else if (errno == EACCES || errno == EPERM)
			print_error("Minishell: cd: ", arg[0], ": Permission denied");
		else
			print_error("Minishell: cd: ", arg[0], ": Not a directory");
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
	if (!arg || ft_strncmp(arg[0], "~", 1) == 0
		|| ft_strncmp(arg[0], home, ft_strlen(home)) == 0)
	{
		if (create_path(home, arg))
			return (1);
		env_update(data, oldpwd);
	}
	else
	{
		directory_error(arg);
		free(oldpwd);
	}
	free(home);
	return (0);
}
