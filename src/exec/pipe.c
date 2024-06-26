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

static int close_fd(int fd)
{
    if (fd != -1)
    {
        close(fd);
        return 0;
    }
    return 1;
}
void close_secure()
    {
        int i;
        i = 3;
        while (i < 1024)
        {
            close(i);
            i++;
        }
    }

void handle_heredocs(t_data *data, int i)
{
    char *line;
    int j = 0;
    while (data->output->h_doc[i][j] != NULL)
    {
        char *tmpfile = ft_strjoin("tmp_files/",data->output->h_doc[i][j]);
        int fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("open_dans_heredoc");
            return;
        }
while ((line = readline(">")) != NULL)
{
    if (strcmp(line, data->output->h_doc[i][j]) == 0)
    {
        free(line);
        break;
    }
    write(fd, line, strlen(line));
    write(fd, "\n", 1);
    free(line);
}
        close(fd);
        if (data->output->h_doc[i][j + 1])
            unlink(tmpfile);
        free(tmpfile);
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
            close_fd(outfd);
        }
        
        outfd = open(data->output->outfile[i][j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfd < 0) 
        {
            perror("open_outfile");
            return ;   
        }
        if (data->output->outfile[i][j + 1])
            close_fd(outfd);
        j++;
    }
    if (data->output->append[i] == 0)
    {
        dup2(outfd, STDOUT_FILENO);
    close_fd(outfd);
    }
}

void create_outfiles_append(t_data *data, int i)
{
    int outfd = -1;
    int j = 0;
    while (data->output->outfile_append[i][j] != NULL) 
    {
        if (outfd != -1) 
        {
            close_fd(outfd);
        }
        outfd = open(data->output->outfile_append[i][j], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (outfd < 0) 
        {
            perror("open_outfile_append");
            return ;
        }
        if (data->output->outfile_append[i][j + 1])
            close_fd(outfd);
        j++;
    }
    if (data->output->append[i] == 1)
    {
        dup2(outfd, STDOUT_FILENO);
        close_fd(outfd);
    }   
}
void create_infiles(t_data *data, int i)
{
    int infd = -1;
    int j = 0;
    while (data->output->infile[i][j] != NULL) 
    {
        if (infd != -1) 
            close_fd(infd); 
        infd = open(data->output->infile[i][j], O_RDONLY);
        if (infd < 0) 
        {
            perror("open_infile");
            exit(1);
        }
        if (data->output->infile[i][j + 1])
            close_fd(infd);
        j++;
    }
    if (data->output->here_d[i] == 0)
        {
        dup2(infd, STDIN_FILENO);
            close_fd(infd);
        }
}
void create_infiles_heredoc(t_data *data, int i)
{
        char *tmpfile;
    int infd = -1;
    int j = 0;
    while (data->output->h_doc[i][j] != NULL) 
        j++;
    if (data->output->h_doc[i][j - 1])
    {
        tmpfile = ft_strjoin("tmp_files/",data->output->h_doc[i][j - 1]);
        if (infd != -1) 
            close_fd(infd); 
        infd = open(tmpfile, O_RDONLY);
        if (infd < 0) 
        {
            perror("ooooopen_heredoc");
            return;
        }
    }
    if (data->output->here_d[i] == 1)
        {
        dup2(infd, STDIN_FILENO);
            close_fd(infd);
            }
    if (data->output->h_doc[i][j - 1] != NULL)
    {
        unlink(tmpfile);
        free(tmpfile);
    }
}

int my_pipe(t_data *data, char *str)
{
int status = 0;

int i = 0;
int *son_pid;
int nbr_pipe;
int original_stdin = dup(STDIN_FILENO);
if (original_stdin == -1) {
    perror("dup");
    return 1;
}
close(original_stdin);
int original_stdout = dup(STDOUT_FILENO);
if (original_stdout == -1) {
    perror("dup");
    return 1;
}
close(original_stdout);
nbr_pipe = 0;
while (data->command->cmd[nbr_pipe + 1])
    nbr_pipe++;
son_pid = ft_calloc(nbr_pipe + 1, sizeof(int));
if (son_pid == NULL)
    return (1);
if (nbr_pipe == 0) 
{
    if (data->output->h_doc[i] && *data->output->h_doc[i] != NULL)
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
    free(son_pid);
    exec(data, data->command->cmd[0], data->command->arg[0], str);
    dup2(original_stdin, STDIN_FILENO);
    close_fd(original_stdin);
    dup2(original_stdout, STDOUT_FILENO);
    close_fd(original_stdout);
    close_secure();
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
        close_fd(fd[0]);
        close_fd(fd[1]);
        free(son_pid);
        return (1);
    }
    else if (son_pid[i] == 0) 
    {
        if (data->output->h_doc[i] != NULL && *data->output->h_doc[i] != NULL)
        {
            handle_heredocs(data, i);
            create_infiles_heredoc(data, i);
        }
        else if (data->output->infile[i]) 
            create_infiles(data, i);
        else 
        {
             dup2(fd_in, STDIN_FILENO);
            close_fd(fd_in);
        }
        
        if (data->output->outfile[i]) 
            create_outfiles(data, i);
        if (data->output->outfile_append[i]) 
            create_outfiles_append(data, i);
        

        if (i != nbr_pipe )
            dup2(fd[1], STDOUT_FILENO);
          close_fd(fd[1]);
          close_fd(fd[0]);
        exec(data, data->command->cmd[i], data->command->arg[i], str);
        exit(127);
    } 
    else
    {
        close_fd(fd[1]);
          if (i != 0) {
                close_fd(fd_in);
          }
        fd_in = fd[0];
        close_fd(fd[0]);
        if (data->output->here_d[i] == 1)
            waitpid(son_pid[i], &status, 0);
        i++;
    }
}
i = 0;
while (i <= nbr_pipe) {
    if (data->output->here_d[i] == 0) 
        waitpid(son_pid[i], &status, 0);
close_secure();        
close_fd(fd[0]);
        close_fd(fd[1]);
    i++;
}
        free(son_pid);
        close_fd(fd_in);

        dup2(original_stdin, STDIN_FILENO);
        close_fd(original_stdin);
        dup2(original_stdout, STDOUT_FILENO);
        close_fd(original_stdout);


return 0;

}

/*
int my_pipe(t_data *data, char *str)
{
int status = 0;

int i = 0;
int *son_pid;
int nbr_pipe;
int original_stdin = dup(STDIN_FILENO);
if (original_stdin == -1) {
    perror("dup");
    return 1;
}
int original_stdout = dup(STDOUT_FILENO);
if (original_stdout == -1) {
    perror("dup");
    return 1;
}
nbr_pipe = 0;
while (data->command->cmd[nbr_pipe + 1])
    nbr_pipe++;
son_pid = ft_calloc(nbr_pipe + 1, sizeof(int));
if (son_pid == NULL)
    return (1);
if (nbr_pipe == 0) 
{
    if (data->output->h_doc[i] && *data->output->h_doc[i] != NULL)
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
     dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
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
        if (data->output->h_doc[i] != NULL && *data->output->h_doc[i] != NULL)
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
         dup2(original_stdin, STDIN_FILENO);
        close(original_stdin);
        dup2(original_stdout, STDOUT_FILENO);
        close(original_stdout);
        exit(1);
    } 
    else if (son_pid[i] > 0)
    {
        close(fd[1]);
        fd_in = fd[0];
        if (data->output->here_d[i] == 1)
            waitpid(son_pid[i], &status, 0);
    }
        i++;
}
i = 0;
while (i <= nbr_pipe)
{
    if (data->output->here_d[i] == 0)
        waitpid(son_pid[i], &status, 0);
    i++;
}

free(son_pid);
return 0;

}*/