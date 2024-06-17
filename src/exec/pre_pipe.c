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
int outfile = -1;
int infile = -1;

nbr_pipe = 0;
while (data->command->cmd[nbr_pipe + 1])
    nbr_pipe++;
son_pid = ft_calloc(nbr_pipe + 2, sizeof(int));
if (son_pid == NULL)
    return (1);
if (nbr_pipe == 0) 
{
    if (data->outfiles[0] != NULL)
    {
        outfile = open(data->outfiles[0], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        infile = open(data->infiles[i], O_RDONLY);
        if (outfile == -1 || infile == -1)
        {
            perror("open");
            return 1;
        }
        if (infile != -1)
        {
            if (dup2(infile, STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
        }
        if (outfile != -1)
        {
            if (dup2(outfile, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
        }
    }
    exec(data, data->command->cmd[0], data->command->arg[0], str);
    if (outfile != -1)
        close(outfile);
    if (infile != -1)
        close(infile);
    return 0;
}
int fd[2];


int fd_in = 0;  /* Backup of the input for the next command */

while (i <= nbr_pipe)
{
    if (data->outfiles[i] != NULL)
    {
        outfile = open(data->outfiles[i], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        if (outfile == -1)
        {
            perror("open");
            return 1;
        }
    }
        if (data->infiles[i] != NULL)
    {
        infile = open(data->infiles[i], O_RDONLY);
        if (infile == -1)
        {
            perror("open");
            return 1;
        }
    }
    pipe(fd); 
    son_pid[i] = fork();
    if (son_pid[i] == -1)
        return(1);
    else if (son_pid[i] == 0) 
    {
        if (infile != -1)
        {
            if (dup2(infile, STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
        }
        if (i == nbr_pipe && outfile != -1)
        {
            if (dup2(outfile, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
        }
        dup2(fd_in, STDIN_FILENO);  /* Change the input according to the old one */
        if (i != nbr_pipe)
            dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);  /* Close the reading end of the pipe, we don't need it */
        exec(data, data->command->cmd[i], data->command->arg[i], str);
        if (infile != -1)
            close(infile);
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        if (outfile != -1)
            close(outfile);
        if (infile != -1)
        {
            close(infile);
            infile = -1;
        }
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



/*
int fd_in = 0;
while (i <= nbr_pipe)
{
    pipe(fd); // Create a pipe 

    if (data->outfiles[i] != NULL)
    {
        outfile = open(data->outfiles[i], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        if (outfile == -1)
        {
            perror("open");
            return 1;
        }
    }
    if (data->infiles[i] != NULL)
    {
        infile = open(data->infiles[i], O_RDONLY);
        if (infile == -1)
        {
            perror("open");
            return 1;
        }
    }
    if (data->heredocs[i] != NULL)
    {
        infile = handle_heredoc(data->delimiter[i]);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        dup2(fd_in, STDIN_FILENO);  Change the input according to the old one 

        if (infile != -1)
        {
            dup2(infile, STDIN_FILENO);
            close(infile);
        }
        if (outfile != -1)
        {
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
        if (i != nbr_pipe)
        {
            dup2(fd[1], STDOUT_FILENO);  For the next command 
        }

        close(fd[0]);  Not needed anymore 

        exec(data, data->command->cmd[0], data->command->arg[0], str);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);  Wait for the child process to finish 
        close(fd[1]);  Not needed anymore 
        fd_in = fd[0];  Save the input for the next command 
    }
}*/