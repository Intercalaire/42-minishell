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
#include "../../include/parsing/minishell.h"
#include <limits.h>



int cd(t_data *data, char **arg)
{
    int k;
    char *oldpwd;
    char *newpwd;
    char *home;
    char *error_msg;

    k = search_env(data, "HOME");
    if (k == -1)
        return (1);
    oldpwd = ft_calloc(PATH_MAX, sizeof(char));
    getcwd(oldpwd, PATH_MAX);
    home = ft_strdup(data->env[k] + 5);
    printf("\n\nhome = |%s|\n\n", home);
    if (!arg || ft_strncmp(arg[0], "~", 1) == 0)
        chdir(home);
    else
    {
        if (chdir(arg[0]) != 0)
        {
        error_msg = ft_calloc(strlen("cd: ") + strlen(arg[0]) + 1, sizeof(char));
            ft_strlcpy(error_msg, "cd: ", strlen("cd: ") + 1);
            ft_strlcat(error_msg, arg[0], strlen("cd: ") + strlen(arg[0]) + 1);
            perror(error_msg);
            free(error_msg);
        }
    }
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
free(oldpwd);
free(newpwd);
free(home);
return (0);
}