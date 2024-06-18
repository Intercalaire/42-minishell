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
        dup2(fd_in, STDIN_FILENO);  

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
            dup2(fd[1], STDOUT_FILENO);  
        }

        close(fd[0]);  Not needed anymore 

        exec(data, data->command->cmd[0], data->command->arg[0], str);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);  
        close(fd[1]);  
        fd_in = fd[0];  
    }
}*/



typedef struct command_data {
    int infile;
    int outfile;
    int fd[2];
    int i;
    int nbr_pipe;
    char *str;
} command_data_t;

void pre_pipe(data_t *data, int nbr_pipe, char *str)
{
    command_data_t cmd_data;
    int fd[2];
    int fd_in = 0;
    int i = 0;

    while (i <= nbr_pipe)
    {
        pipe(fd); // Create a pipe 

        cmd_data.fd[0] = fd[0];
        cmd_data.fd[1] = fd[1];
        cmd_data.i = i;
        cmd_data.nbr_pipe = nbr_pipe;
        if (data->outfiles[i] != NULL)
        {
            cmd_data.outfile = open(data->outfiles[i], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
            if (cmd_data.outfile == -1)
            {
                perror("open");
                return;
            }
        }

        if (data->infiles[i] != NULL)
        {
            cmd_data.infile = open(data->infiles[i], O_RDONLY);
            if (cmd_data.infile == -1)
            {
                perror("open");
                return;
            }
            execute_command(data, &cmd_data, str);
            close(cmd_data.infile);
        }

        if (data->EOF[i] != NULL)
        {
            cmd_data.infile = handle_heredoc(data->EOF[i]);
            if (cmd_data.infile == -1)
            {
                perror("handle_heredoc");
                return;
            }
            execute_command(data, &cmd_data, str);
            close(cmd_data.infile);
        }

        if (cmd_data.outfile != -1)
        {
            close(cmd_data.outfile);
        }

        fd_in = fd[0];
        i++;
    }
}

void execute_command(data_t *data, command_data_t *cmd_data, char *str)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        dup2(cmd_data->infile, STDIN_FILENO);

        if (cmd_data->outfile != -1)
        {
            dup2(cmd_data->outfile, STDOUT_FILENO);
        }
        else if (cmd_data->i != cmd_data->nbr_pipe)
        {
            dup2(cmd_data->fd[1], STDOUT_FILENO);  
        }

        close(cmd_data->fd[0]);  // Not needed anymore 

        exec(data, data->command->cmd[0], data->command->arg[0], str);
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);  
        close(cmd_data->fd[1]);  
    }
}