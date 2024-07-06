#include "../../include/parsing/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

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
            close_fd(infd); // Assurez-vous de fermer le descripteur précédent
        infd = open(data->output->infile[i][j], O_RDONLY);
        if (infd < 0) 
        {
            perror("open_infile");
            return;
        }
        j++;
    }
    if (infd != -1 && data->output->here_d[i] == 0) // Correction pour s'assurer que infd est valide
    {
        dup2(infd, STDIN_FILENO);
        close_fd(infd);
    }
}

void create_infiles_heredoc(t_data *data, int i)
{
    char *tmpfile;
    int j = 0;
    int infd;
    while (data->output->h_doc[i][j] != NULL) 
        j++;
    if (j > 0 && data->output->h_doc[i][j - 1]) // Vérifiez si j > 0 pour éviter un accès hors limites
    {
        tmpfile = ft_strjoin("tmp_files/", data->output->h_doc[i][j - 1]);
        infd = open(tmpfile, O_RDONLY, 0644); // Correction: O_RDONLY sans O_CREAT
        if (infd < 0) 
        {
            perror("open_heredoc");
            free(tmpfile);
            return;
        }
        if (data->output->here_d[i] == 1)
        {
            dup2(infd, STDIN_FILENO);
            close_fd(infd);
        }
        unlink(tmpfile);
        free(tmpfile);
    }
}