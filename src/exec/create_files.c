#include "../../include/parsing/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int create_outfiles(t_data *data, int i)
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
            perror(data->output->outfile[i][j]);
            return (1);   
        }
        j++;
    }
    if (data->output->append[i] == 0)
    {
        dup2(outfd, STDOUT_FILENO);
        close_fd(outfd);
    }
    return (0);
}

int create_outfiles_append(t_data *data, int i)
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
            perror(data->output->outfile_append[i][j]);
            return (1);
        }
        j++;
    }
    if (data->output->append[i] == 1)
    {
        dup2(outfd, STDOUT_FILENO);
        close_fd(outfd);
    }  
    return (0);
}
int create_infiles(t_data *data, int i)
{
    int infd = -1;
    int j = 0;
    while (data->output->infile[i][j] != NULL) 
    {
        if (infd != -1) 
            close_fd(infd); // Assurez-vous de fermer le descripteur précédent
        infd = open(data->output->infile[i][j], O_RDONLY);
        if (infd < 0) 
        {
            perror(data->output->infile[i][j]);
            return (1);
        }
        j++;
    }
    if (infd != -1 && data->output->here_d[i] == 0) // Correction pour s'assurer que infd est valide
    {
        dup2(infd, STDIN_FILENO);
        close_fd(infd);
    }
    return (0);
}

int create_infiles_heredoc(t_data *data, int i)
{
    char *tmpfile;
    int j = 0;
    int infd;
    while (data->output->h_doc[i][j] != NULL) 
        j++;
    if (j > 0 && data->output->h_doc[i][j - 1])
    {
        tmpfile = ft_strjoin("tmp_files/", data->output->h_doc[i][j - 1]);
        infd = open(tmpfile, O_RDONLY, 0644);
        if (infd < 0) 
        {
            ft_putstr_fd("testsetsts\n\n\n", 2);
            perror(data->output->h_doc[i][j - 1]);
            free(tmpfile);
            return (1);
        }
        if (data->output->here_d[i] == 1)
        {
            dup2(infd, STDIN_FILENO);
            close_fd(infd);
        }
        unlink(tmpfile);
        free(tmpfile);
    }
    return (0);
}
