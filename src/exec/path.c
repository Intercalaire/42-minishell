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
#include <fcntl.h>



//dans les cas ou c'est different de echo, cd, pwd, export, unset, env, exit
void path(t_data *data, char *cmd, char **arg)
{
	int path;
	char **var;
	int i;
	char *full_path;
	pid_t pid;
    char *tmp;
    char **args;
    int arg_count = 0;
    data->sig_status = 1;

    args = NULL;
    full_path = NULL;
	pid = fork();
	i = 0;
	path = search_env(data, "PATH");
    if (path == -1)
    {
        printf("minishell: %s: No such file or directory\n", cmd);
        data->exit_status = 127;
        return ;
    }
	var = ft_split(data->env[path] + 5, ':');
	while (var[i])
	{
		if (!ft_strncmp(var[i], "/bin", 5))
			break ;
		i++;
	}
ft_sig(data);
if (pid == 0)
{
    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
{
    // cmd est un chemin absolu ou relatif, essayez de l'exécuter directement
    if (execve(cmd, args, data->env) == -1)
    {
        perror(cmd);
        exit(127); // Sortie avec une erreur si execve échoue
    }
}
    else 
    {
        tmp = ft_strjoin(var[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
    }    
    if (arg)
        while (arg[arg_count]) 
            arg_count++;
    args = ft_calloc((arg_count + 2) , sizeof(char *));
    args[0] = ft_strdup(cmd);
    int j = 0;
    if (arg)
    {
        while (arg[j]) 
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
            data->exit_status = 127;
            exit(127);
        }
        else if (errno == EACCES)
        {
            perror(args[0]);
            data->exit_status = 1;
            exit(1);
        }
        else
        {
            perror(args[0]);
            data->exit_status = 127;
            exit(127);
        }
    }
}
else
{
        int status;
    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        data->exit_status = 1;
    }
    else
{
    if (WIFEXITED(status))
    {
        int exit_status = WEXITSTATUS(status);
        data->exit_status = exit_status; // Le processus enfant s'est terminé normalement
    }
   else if (WIFSIGNALED(status))
    {
        int term_sig = WTERMSIG(status);
        if (term_sig == SIGSEGV)
        {
            printf("Segmentation fault\n");
            data->exit_status = 128 + SIGSEGV; // Convention pour signaler un segfault
        }
        else if (term_sig == SIGINT)
        {
            printf("Interruption par signal SIGINT\n");
            data->exit_status = 128 + SIGINT;
        }
        else if (term_sig == SIGABRT)
        {
            printf("Abandon (signal SIGABRT)\n");
            data->exit_status = 128 + SIGABRT;
        }
        else if (term_sig == SIGFPE)
        {
            printf("Erreur de calcul flottant (signal SIGFPE)\n");
            data->exit_status = 128 + SIGFPE;
        }
        else if (term_sig == SIGILL)
        {
            printf("Instruction illégale (signal SIGILL)\n");
            data->exit_status = 128 + SIGILL;
        }
        else if (term_sig == SIGTERM)
        {
            printf("Terminaison (signal SIGTERM)\n");
            data->exit_status = 128 + SIGTERM;
        }
    }
}
}
        if (var)
            ft_free_strtab(var);
        if (full_path)
            free(full_path);         
        if (args)
            ft_free_strtab(args);
}
