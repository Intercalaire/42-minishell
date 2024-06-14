/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:10:52 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/15 10:42:53 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int my_pipe(t_data *data)
{

int i;
int *son_pid;
int *fd;
int nbr_pipe;

nbr_pipe = 0;
i = 0;
while (data->command->cmd[nbr_pipe])
    nbr_pipe++;
son_pid = ft_calloc(nbr_pipe + 1, sizeof(int));
if (son_pid == NULL)
    return (1);
if (nbr_pipe == 0) 
{
    exec(data, data->command->cmd[0], data->command->arg[0]);
    return 0;
}
fd = ft_calloc(2, sizeof(int));
while (i <= nbr_pipe)
{
    pipe(fd); 
    son_pid[i] = fork();
    if (son_pid[i] == -1)
        return(1);
    else if (son_pid[i] == 0) 
    {
        if (i != nbr_pipe - 1)
            dup2(fd[1], STDOUT_FILENO);
        if (i != 0) {
            dup2(fd[0], STDIN_FILENO);
        }
        close(fd[0]);
        close(fd[1]);
        exec(data, data->command->cmd[i], data->command->arg[i]);
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        wait(NULL);
        close(fd[0]);
        if (i != nbr_pipe - 1)
            close(fd[1]);
        i++;
    }
}
    free(fd);
    return (0);
}
