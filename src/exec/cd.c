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
    char *home;

    k = search_env(data, "HOME");
    if (k == -1)
        return (1);
    home = ft_strdup(data->env[k] + 5);
    printf("\n\nhome = |%s|\n\n", home);
    if (arg[0] == NULL || ft_strncmp(arg[0], "~", 1) == 0)
        chdir(home);
    else if (ft_strncmp(arg[0], "-", 1) == 0) 
    {
        k = search_env(data, "OLDPWD");
        if (k == -1)
        {
            return (1);
        }
        else 
        {
            oldpwd = ft_strdup(data->env[k] + 7);
            printf("\n\nold pwd = |%s|\n\n", oldpwd);
            chdir(oldpwd);
        }
    } 
    else
    {
        if (chdir(arg[0]) != 0) 
            perror("cd");
    }
 

oldpwd = getcwd(NULL, 0);
strncpy(data->env[search_env(data, "OLDPWD")] + 7, oldpwd, PATH_MAX - 7);
strncpy(data->env[search_env(data, "PWD")] + 4, oldpwd, PATH_MAX - 4);
free(oldpwd);
return (0);
}