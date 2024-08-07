#include "../../include/parsing/minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	create_outfiles(t_data *data, int i)
{
	int	outfd;
	int	j;

	outfd = -1;
	j = 0;
	while (data->output->outfile[i][j] != NULL)
	{
		if (outfd != -1)
		{
			close_fd(outfd);
		}
		outfd = open(data->output->outfile[i][j], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (outfd < 0)
		{
			print_error("Minishell : ", data->output->outfile[i][j],
				": No such file or directory");
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

int	create_outfiles_append(t_data *data, int i)
{
	int	outfd;
	int	j;

	outfd = -1;
	j = 0;
	while (data->output->outfile_append[i][j] != NULL)
	{
		if (outfd != -1)
		{
			close_fd(outfd);
		}
		outfd = open(data->output->outfile_append[i][j],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfd < 0)
		{
			print_error("Minishell : ", data->output->outfile_append[i][j],
				": No such file or directory");
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
int	create_infiles(t_data *data, int i)
{
	int	infd;
	int	j;

	infd = -1;
	j = 0;
	while (data->output->infile[i][j] != NULL)
	{
		if (infd != -1)
			close_fd(infd);
		infd = open(data->output->infile[i][j], O_RDONLY);
		if (infd < 0)
		{
			print_error("Minishell : ", data->output->infile[i][j],
				": No such file or directory");
			return (1);
		}
		j++;
	}
	if (infd != -1 && data->output->here_d[i] == 0)
	{
		dup2(infd, STDIN_FILENO);
		close_fd(infd);
	}
	return (0);
}

int	create_infiles_heredoc(t_data *data, int i)
{
	char	*tmpfile;
	int		j;
	int		infd;

	j = 0;
	while (data->output->h_doc[i][j] != NULL)
		j++;
	if (j > 0 && data->output->h_doc[i][j - 1])
	{
		tmpfile = ft_strjoin("tmp_files/", data->output->h_doc[i][j - 1]);
		infd = open(tmpfile, O_RDONLY, 0644);
		if (infd < 0)
		{
			print_error("Minishell : ", data->output->h_doc[i][j - 1],
				": No such file or directory");
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
