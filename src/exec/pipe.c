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
#include <signal.h>
int close_fd(int fd)
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
			close_fd(i);
			i++;
		}
	}

void print_error(char *start, char *cmd, char *str)
{
	ft_putstr_fd(start, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}
char *get_env_value(t_data *data, char *varName)
{
	int index = search_env(data, varName);
	if (index == -1) return NULL; 

	char *entry = data->env[index];
	char *value = strchr(entry, '='); 
	if (!value) return NULL;

	return value + 1; 
}


int handle_special_case(t_data *data, char **ptr) {
    int size = strlen(ft_itoa(data->exit_status));
    *ptr += 2; 
    return size;
}

int handle_env_var(t_data *data, char **ptr) {
    char *end = *ptr + 1;
    while (isalnum(*end) || *end == '_') end++;
    int len = end - (*ptr + 1);
    if (len > 0) {
        char varName[256];
        strncpy(varName, *ptr + 1, len);
        varName[len] = '\0';
        char *value = get_env_value(data, varName);
        *ptr = end; 
        return value ? strlen(value) : 0;
    }
    *ptr = end; 
    return 0;
}

int calculate_size_needed(t_data *data, char *line) {
    int size_needed = 1; 
    char *ptr = line;
    while (*ptr) {
        if (*ptr == '$') {
            if (*(ptr + 1) == '?') {
                size_needed += handle_special_case(data, &ptr);
            } else {
                size_needed += handle_env_var(data, &ptr);
            }
        } else {
            size_needed++;
			ptr++;
        }
    }
    return size_needed;
}

void handle_env_var2(t_data *data, char **temp, char **ptr) {
    char *end = *ptr + 1;
    while (isalnum(*end) || *end == '_') end++;
    int len = end - (*ptr + 1);
    if (len > 0) {
        char varName[256];
        strncpy(varName, *ptr + 1, len);
        varName[len] = '\0';
        char *value = get_env_value(data, varName);
        if (value) {
            strcpy(*temp, value);
            *temp += strlen(value);
        }
    }
    *ptr = end;
}

void handle_special_case2(t_data *data, char **temp, char **ptr) {
    char *value = ft_itoa(data->exit_status);
    strcpy(*temp, value);
    *temp += strlen(value);
	free(value);
    *ptr += 2;
}

void copy_normal_chars(char **temp, char **ptr) {
    **temp = **ptr;
    (*temp)++;
    (*ptr)++;
}
void build_final_string(t_data *data, char *result, char *line) {
    char *temp = result;
    char *ptr = line;
    while (*ptr) 
	{
        if (*ptr == '$') 
		{
            if (*(ptr + 1) == '?')
                handle_special_case2(data, &temp, &ptr);
			else
                handle_env_var2(data, &temp, &ptr);
		}
        else
            copy_normal_chars(&temp, &ptr);
    }
    *temp = '\0';
}

char *expand_env_vars(t_data *data, char *line) {
    int size_needed = calculate_size_needed(data, line);
    char *result = malloc(size_needed);
    if (!result) return NULL;
    build_final_string(data, result, line);
    return result;
}

void signal_handler(int signum) 
{
	close(0);
	rl_on_new_line();
	g_sig = signum;
	write(STDOUT_FILENO, "\n", 1);
}

int create_tmp_file(char *tmpfiles) 
{   
	int fd; 
    fd = open(tmpfiles, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        print_error("Minishell: ", tmpfiles, ": No such file or directory\n");
        free(tmpfiles);
    }
    return fd; 
}

void handle_user_input(t_data *data, char *end_word) 
{
    char *line;
	int is_interactive;
    char *prompt;
	char *expanded_line;

    signal(SIGINT, signal_handler);
	is_interactive = isatty(STDIN_FILENO);
	prompt = NULL;
	if (is_interactive) 
		prompt = "> ";
    line = readline(prompt);
    while (line != NULL)
	{
    	if (strcmp(line, end_word) == 0) 
		{
    		free(line);
			break;
    	}
    	expanded_line = expand_env_vars(data, line);
    	write(data->output->fd, expanded_line, strlen(expanded_line));
    	write(data->output->fd, "\n", 1);
    	free(expanded_line);
    	free(line);
    	line = readline(prompt);
    }
}

int cleanup_and_close(t_data *data, char *tmpfiles, char *next_file) {
    if (g_sig == SIGINT) 
	{
        close(data->output->fd);
        data->output->fd = open(tmpfiles, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		write(data->output->fd, "", 0);
		close(data->output->fd);
		//ajouter un free de tout tout tout
		// free(str);
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
	return 0;
}

void handle_heredocs(t_data *data, int i) 
{
	int j;
	char *tmpfiles ;

	j = 0;
    while (data->output->h_doc[i][j]) 
	{
		tmpfiles = ft_strjoin("tmp_files/", data->output->h_doc[i][j]);
        data->output->fd = create_tmp_file(tmpfiles);
        if (data->output->fd == -1) 
			return;
        handle_user_input(data, data->output->h_doc[i][j]);
        if (cleanup_and_close(data, tmpfiles, data->output->h_doc[i][j + 1]))
			break;
		free(tmpfiles);
        j++;
    }
    signal(SIGINT, SIG_DFL);
}

void execute_heredoc(t_data *data, int i)
{
	pid_t pid;
	int status;
	
 		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return;
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
int check_open_files(t_data *data, int i)
{
	int return_value;

	return_value = 0;
	if (data->output->h_doc[i] && data->output->here_d[i] == 1)
		return_value = create_infiles_heredoc(data, i);
	if (data->output->infile[i] && data->output->here_d[i] == 0) 
		return_value = create_infiles(data, i);
	if (data->output->outfile[i] && *data->output->outfile[i]) 
		return_value = create_outfiles(data, i);
	if (data->output->outfile_append[i] && *data->output->outfile_append[i]) 
		return_value = create_outfiles_append(data, i);
	return (return_value);
}

int is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);

}
int execute_builtin_with_redirection(t_data *data, char *cmd, char **arg)
{
	data->fd_pipe->std_in = dup(STDIN_FILENO);
	data->fd_pipe->std_out = dup(STDOUT_FILENO);
	check_open_files(data, 0);
    exec(data, cmd, arg);
    dup2(data->fd_pipe->std_in, STDIN_FILENO);
    dup2(data->fd_pipe->std_out, STDOUT_FILENO);
    close(data->fd_pipe->std_in);
    close(data->fd_pipe->std_out);
	return 0;
}

int start_process(t_data *data)
{
		if (is_builtin(data->command->cmd[0]))
		{
			if (execute_builtin_with_redirection(data, data->command->cmd[0], data->command->arg[0]))
				return (1);
		}
		else
			if (exec(data, data->command->cmd[0], data->command->arg[0]))
				return (1);
		// reset_fd(data);
	   return (0);
}


void child_processus(t_data *data, int *pipefd, int i)
{

		if (i != 0) 
		{
                if (dup2(data->fd_pipe->fd_in, STDIN_FILENO) == -1) 
				{
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close_fd(data->fd_pipe->fd_in);
		}
		if (i != data->meter->nbr_pipe) 
		{
        	if (dup2(pipefd[1], STDOUT_FILENO) == -1) 
			{
        	    perror("dup2");
        	    exit(EXIT_FAILURE);
        	}
        	close_fd(pipefd[1]);
        	close_fd(pipefd[0]);
        }
		check_open_files(data, i);
		exec(data, data->command->cmd[i], data->command->arg[i]);

		}

int parent_processus(t_data *data, int *pipefd, int i)
{
	// int status;

	signal(SIGINT, SIG_DFL);
	data->sig_status = 1;
	ft_sig(data);
	if (i != 0) 
        close(data->fd_pipe->fd_in);
    if (i != data->meter->nbr_pipe ) 
	{
        close(pipefd[1]);
        data->fd_pipe->fd_in = pipefd[0]; 
	}
	// waitpid(pid, &status, 0);
    //     if (WIFEXITED(status))
	// 		return (1);
	return (0);
}
int execute_fork(t_data *data, int i, int *pipefd)
{
	pid_t pid;

	pid = fork();
	if (pid == -1) 
	{
		perror("fork");
		return (2);
	}
	if (pid == 0) 
	{
		child_processus(data, pipefd, i);
		//ft_end_error_prog(data, str, NULL);
		//ajouter un free de tout tout tout
		exit(127);
	} 
	else if (parent_processus(data, pipefd, i))
		return (1);
	return (0);
}

int my_pipe(t_data *data)
{
    int pipefd[2];
	int i ;

	data->fd_pipe->fd_in = 0;
	i = 0;
	while (i <= data->meter->nbr_pipe)
	{
		if (data->output->h_doc[i] && *data->output->h_doc[i] != NULL)
			execute_heredoc(data, i);
		i++;
	}
	if (data->meter->nbr_pipe == 0)
	{
		if (start_process(data))
			return (1);
	}
	else
	{
	i = 0;
		while (i <= data->meter->nbr_pipe)
		{
			if (i != data->meter->nbr_pipe ) {
				if (pipe(pipefd) == -1) {
					perror("pipe");
					return (1);
				}
			}
			if (execute_fork(data, i, pipefd))
				return (1);
			i++;
		}
		i = 0;
		while (i <= data->meter->nbr_pipe) 
		{
			wait(NULL);
			i++;
		}
	}
	return (0);

}
