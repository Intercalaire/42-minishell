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

/*
int absolute()
{
	chdir(data->command->arg[i][j]);

}

int relative()
{

}

void cd(t_data *data, int i, int j)
{
	int k;

	k = search_env(data, "HOME");
	if (k = -1)
		exit_error("no home found");
	if (ft_strncmp(data->command->arg[i][j], data->env[k], ft_strlen(data->env[k] == 0)
		absolute();
	else
		relative();







	char *str;
	str = ft_substr(s->pwd, "/");
	str = ft_substr(s->pwd, arg);
	if (chdir(str) == -1)
		error("Error");
}
*/

void cd(t_data *data, char **arg)
{
    int k;
    char *oldpwd;
    char *home;

    k = search_env(data, "HOME");
    if (k == -1)
        return;
    home = data->env[k] + 5; // Retirer le début du chemin

    if (data->command->arg[0][0] == NULL || ft_strncmp(data->command->arg[0][0], "~", 1) == 0) {
        // Si aucun argument ou si l'argument est "~", aller au répertoire HOME
        chdir(home);
    } else if (ft_strncmp(data->command->arg[0][0], "-", 1) == 0) {
        // Si l'argument est "-", aller au répertoire précédent
        k = search_env(data, "OLDPWD");
        if (k == -1) {
            fprintf(stderr, "cd: OLDPWD not set\n");
        } else {
            oldpwd = data->env[k] + 7; // Retirer le début du chemin
            chdir(oldpwd);
        }
    } else {
        // Sinon, aller au répertoire spécifié
        if (chdir(data->command->arg[0][0]) != 0) {
            perror("cd");
        }
    }

oldpwd = getcwd(NULL, 0);
strncpy(data->env[search_env(data, "OLDPWD")] + 7, oldpwd, PATH_MAX - 7);
strncpy(data->env[search_env(data, "PWD")] + 4, oldpwd, PATH_MAX - 4);
free(oldpwd);
}