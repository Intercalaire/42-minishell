/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredocs_more_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 05:18:20 by hsolet            #+#    #+#             */
/*   Updated: 2024/08/08 05:18:36 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static void	signal_handler(int signum)
{
	close(0);
	rl_on_new_line();
	g_sig = signum;
	write(STDOUT_FILENO, "\n", 1);
}

static void	handle_user_input(t_data *data, char *end_word, int i)
{
	char	*line;
	int		is_interactive;
	char	*prompt;
	char	*expanded_line;

	signal(SIGINT, signal_handler);
	is_interactive = isatty(STDIN_FILENO);
	prompt = NULL;
	if (is_interactive)
		prompt = "> ";
	line = readline(prompt);
	while (line != NULL)
	{
		if (ft_strcmp(line, end_word) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = expand_env_vars(data, line, i);
		write(data->output->fd, expanded_line, ft_strlen(expanded_line));
		write(data->output->fd, "\n", 2);
		free(expanded_line);
		free(line);
		line = readline(prompt);
	}
}

static int	cleanup_and_close(t_data *data, char *tmpfiles, char *next_file)
{
	if (g_sig == SIGINT)
	{
		close(data->output->fd);
		data->output->fd = open(tmpfiles, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(data->output->fd, "", 0);
		close(data->output->fd);
		free(tmpfiles);
		g_sig = 0;
		return (1);
	}
	else
	{
		close(data->output->fd);
		if (next_file != NULL)
			unlink(tmpfiles);
	}
	return (0);
}

static void	handle_heredocs(t_data *data, int i)
{
	int		j;
	char	*tmpfiles;

	j = 0;
	while (data->output->h_doc[i][j])
	{
		tmpfiles = ft_strjoin("/tmp/", data->output->h_doc[i][j]);
		data->output->fd = create_tmp_file(tmpfiles);
		if (data->output->fd == -1)
			return ;
		handle_user_input(data, data->output->h_doc[i][j], i);
		if (cleanup_and_close(data, tmpfiles, data->output->h_doc[i][j + 1]))
			break ;
		free(tmpfiles);
		j++;
	}
	signal(SIGINT, SIG_DFL);
}

void	execute_heredoc(t_data *data, int i)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		handle_heredocs(data, i);
		ft_end_error_prog(data);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &status, 0);
}
