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
#include "../../include/exec_test/minishell.h"
#include <limits.h>


void cd(t_data *data, char **arg)
{
    int k;
    char *oldpwd;
    char *home;

    k = search_env(data, "HOME");
    if (k == -1)
        return;
    home = data->env[k] + 5;

    if (data->command->arg[0][0] == NULL || ft_strncmp(data->command->arg[0][0], "~", 1) == 0)
        chdir(home);
    else if (ft_strncmp(data->command->arg[0][0], "-", 1) == 0) 
    {
        k = search_env(data, "OLDPWD");
        if (k == -1)
            fprintf(stderr, "cd: OLDPWD not set\n");
        else 
        {
            oldpwd = data->env[k] + 7; 
            chdir(oldpwd);
        }
    } 
    else
    {
        if (chdir(data->command->arg[0][0]) != 0) 
            perror("cd");
    }

oldpwd = getcwd(NULL, 0);
if (search_env(data, "OLDPWD") == -1)
    add_env(data, "OLDPWD", oldpwd);
else
    change_env(data, "OLDPWD", oldpwd);
if (search_env(data, "PWD") == -1)
    add_env(data, "PWD", oldpwd);
else
    change_env(data, "PWD", oldpwd);
free(oldpwd);
}