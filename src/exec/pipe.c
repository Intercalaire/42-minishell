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

int my_pipe(t_data *data, char *str)
{

int i = 0;
int *son_pid;
int nbr_pipe;

nbr_pipe = 0;
while (data->command->cmd[nbr_pipe + 1])
    nbr_pipe++;
son_pid = ft_calloc(nbr_pipe + 1, sizeof(int));
if (son_pid == NULL)
    return (1);
if (nbr_pipe == 0) 
{
    exec(data, data->command->cmd[0], data->command->arg[0], str);
    free(son_pid);
    return (0);
}
int fd[2];


int fd_in = 0;  /* Backup of the input for the next command */

while (i <= nbr_pipe)
{
    pipe(fd); 
    son_pid[i] = fork();
    if (son_pid[i] == -1)
        {
            close(fd[0]);
            close(fd[1]);
            return (1);
        }
    else if (son_pid[i] == 0) 
    {
        dup2(fd_in, STDIN_FILENO);  /* Change the input according to the old one */
        if (i != nbr_pipe)
            dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);  /* Close the reading end of the pipe, we don't need it */
        exec(data, data->command->cmd[i], data->command->arg[i], str);
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        close(fd[1]);  /* Close the writing end of the pipe, we don't need it */
        fd_in = fd[0];  /* Save the input for the next command */
    }
    i++;
}

int status = 0;
i = 0;
while (i <= nbr_pipe)
{
    waitpid(son_pid[i], &status, 0);
    i++;
}

free(son_pid);
return 0;

}
