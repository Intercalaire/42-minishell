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

void handle_heredocs(t_data *data, int i)
{
    int j = 0;
    while (data->output->h_doc[i][j] != NULL)
    {
        char *tmpfile = ft_strjoin("tmp_files/", data->output->h_doc[i][j]);
        int fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("open_dans_heredoc");
            exit(EXIT_FAILURE);
        }

        char buffer[1024];
        ssize_t n;
        while ((n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[n] = '\0';
            if (strcmp(buffer, data->output->h_doc[i][j]) == 0)
                break;
            write(fd, buffer, n);
        }
        close(fd);
        if (data->output->h_doc[i][j + 1])
            unlink(tmpfile);
        j++;
    }
}
void create_outfiles(t_data *data, int i)
{

    int outfd = -1;
    int j = 0;
    while (data->output->outfile[i][j] != NULL) 
    {
        if (outfd != -1) 
        {
            close(outfd);
        }
        outfd = open(data->output->outfile[i][j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfd < 0) 
        {
            perror("open_outfile");
            exit(EXIT_FAILURE);
        }
        j++;
    }
    if (data->output->append == 0)
        dup2(outfd, STDOUT_FILENO);
    close(outfd);
}

void create_outfiles_append(t_data *data, int i)
{
    int outfd = -1;
    int j = 0;
    while (data->output->outfile[i][j] != NULL) 
    {
        if (outfd != -1) 
        {
            close(outfd);  // Close the previous outfile
        }
        outfd = open(data->output->outfile[i][j], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (outfd < 0) 
        {
            perror("open_outfile_append");
            exit(EXIT_FAILURE);
        }
        j++;
    }
    if (data->output->append == 1)
        dup2(outfd, STDOUT_FILENO);
    close(outfd);
}
void create_infiles(t_data *data, int i)
{
    int infd = -1;
    int j = 0;
    while (data->output->infile[i][j] != NULL) 
    {
        if (infd != -1) 
            close(infd); 
        infd = open(data->output->infile[i][j], O_RDONLY);
        if (infd < 0) 
        {
            perror("open_infile");
            exit(EXIT_FAILURE);
        }

        j++;
    }
    if (data->output->here_d == 0)
        dup2(infd, STDIN_FILENO);
    close(infd);
}
void create_infiles_heredoc(t_data *data, int i)
{
    int infd = -1;
    int j = 0;
    while (data->output->h_doc[i][j] != NULL) 
    {
        if (infd != -1) 
            close(infd); 
        infd = open(data->output->h_doc[i][j], O_RDONLY);
        if (infd < 0) 
        {
            perror("open_heredoc");
            exit(EXIT_FAILURE);
        }
        j++;
    }
    if (data->output->here_d == 1)
        dup2(infd, STDIN_FILENO);
    close(infd);
}

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
        if (data->output->h_doc[i])
    {
        handle_heredocs(data, i);
        create_infiles_heredoc(data, i);
    }
    if (data->output->infile[i]) 
        create_infiles(data, i);

    if (data->output->outfile[i]) 
        create_outfiles(data, i);
    if (data->output->outfile_append[i]) 
        create_outfiles_append(data, i);
    exec(data, data->command->cmd[0], data->command->arg[0], str);
    free(son_pid);
    return (0);
}
int fd[2];


int fd_in = 0;

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
    if (data->output->h_doc[i])
    {
        handle_heredocs(data, i);
        create_infiles_heredoc(data, i);
    }
    if (data->output->infile[i]) 
        create_infiles(data, i);

    if (data->output->outfile[i]) 
        create_outfiles(data, i);
    if (data->output->outfile_append[i]) 
        create_outfiles_append(data, i);


    if (i != nbr_pipe)
        dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    exec(data, data->command->cmd[i], data->command->arg[i], str);
    exit(EXIT_SUCCESS);
} 
    else 
    {
        close(fd[1]);
        fd_in = fd[0]; 
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
