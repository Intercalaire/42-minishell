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

char *get_env_value(t_data *data, char *varName)
{
	int index = search_env(data, varName);
	if (index == -1) return NULL; // La variable d'environnement n'a pas été trouvée

	char *entry = data->env[index];
	char *value = strchr(entry, '='); // Trouver le signe '='
	if (!value) return NULL; // Format invalide, pas de valeur

	return value + 1; // Retourner la valeur (après le signe '=')
}

char *expand_env_vars(t_data *data, char *line) {
    int size_needed = 1; // Pour le caractère de fin de chaîne '\0'
    char *ptr = line;

    // Étape 1 : Calculer la taille nécessaire
    while (*ptr) {
        if (*ptr == '$') {
            if (*(ptr + 1) == '?') { // Traitement spécial pour "$?"
                size_needed += strlen(ft_itoa(data->exit_status));
                ptr += 2; // Passer "$?"
            } else {
                char *end = ptr + 1;
                while (isalnum(*end) || *end == '_') end++;
                int len = end - (ptr + 1);
                if (len > 0) { // Si le nom de la variable est non vide
                    char varName[256];
                    strncpy(varName, ptr + 1, len);
                    varName[len] = '\0';
                    char *value = get_env_value(data, varName);
                    if (value) size_needed += strlen(value);
                }
                ptr = end;
            }
        } else {
            size_needed++;
            ptr++;
        }
    }

    // Étape 2 : Allouer suffisamment de mémoire
    char *result = malloc(size_needed);
    if (!result) return NULL;

    // Étape 3 : Construire la chaîne avec les valeurs des variables
    char *temp = result;
    ptr = line;
    while (*ptr) {
        if (*ptr == '$') {
            if (*(ptr + 1) == '?') {
                char *value = ft_itoa(data->exit_status);
                strcpy(temp, value);
                temp += strlen(value);
                ptr += 2;
            } else {
                char *end = ptr + 1;
                while (isalnum(*end) || *end == '_') end++;
                int len = end - (ptr + 1);
                if (len > 0) {
                    char varName[256];
                    strncpy(varName, ptr + 1, len);
                    varName[len] = '\0';
                    char *value = get_env_value(data, varName);
                    if (value) {
                        strcpy(temp, value);
                        temp += strlen(value);
                    }
                }
                ptr = end;
            }
        } else {
            *temp++ = *ptr++;
        }
    }
    *temp = '\0'; // Terminer la chaîne correctement
    return result;
}
void signal_handler(int signum) {
	close(0);
	g_sig = signum;
}
void handle_heredocs(t_data *data, int i)
{
	char *line;
	int j = 0;


	while (data->output->h_doc[i][j] != NULL)
	{
		char *tmpfile = ft_strjoin("tmp_files/", data->output->h_doc[i][j]);
		int fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open_dans_heredoc");
			free(tmpfile);
			return;
		}
		signal(SIGINT, signal_handler);
		int is_interactive = isatty(STDIN_FILENO);
		char *prompt = NULL;
		if (is_interactive) 
			prompt = "> ";
		while ((line = readline(prompt)) != NULL)
		{
			if (strcmp(line, data->output->h_doc[i][j]) == 0)
			{
				free(line);
				break;
			}
			char *expanded_line = expand_env_vars(data, line);
			write(fd, expanded_line, strlen(expanded_line));
			write(fd, "\n", 1);
			free(expanded_line);
			free(line);
		}
		if (g_sig == SIGINT)
			{
				free(line);
				close(fd);
				unlink(tmpfile);
				free(tmpfile);
				g_sig = 0;
				return;
			}
		close(fd);
		if (data->output->h_doc[i][j + 1])
			unlink(tmpfile);
		free(tmpfile);
		j++;
	}
	//signal(SIGINT, SIG_DFL);
}
void execute_heredoc(t_data *data, int i)
{
	pid_t pid;
	int status;
 
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return;
		}
		if (pid == 0)
		{
			handle_heredocs(data, i);
			exit(EXIT_SUCCESS);
		}
		else
		{   
			while (1)
		{
			pid_t wpid = waitpid(pid, &status, WNOHANG);
			if (wpid == -1)
			{
				perror("waitpid");
				break;
			}
			else if (wpid == 0)
			{
				if (g_sig)
				{
					kill(pid, SIGINT);  // Envoyer SIGINT au processus enfant
					g_sig = 0;  // Réinitialiser sigint_received
				}
			}
			else
				break;  // Le processus enfant a terminé
		}
		}
}
void check_open_files(t_data *data, int i)
{
		if (data->output->h_doc[i] != NULL && *data->output->h_doc[i] != NULL)
			create_infiles_heredoc(data, i);
		if (data->output->infile[i]) 
			create_infiles(data, i);
		if (data->output->outfile[i]) 
			create_outfiles(data, i);
		if (data->output->outfile_append[i]) 
			create_outfiles_append(data, i);
}

void reset_fd(t_data *data)
{
	dup2(data->fd_pipe->std_in, STDIN_FILENO);
	close(data->fd_pipe->std_in);
	dup2(data->fd_pipe->std_out, STDOUT_FILENO);
	close(data->fd_pipe->std_out);
}
void end_process(t_data *data, int *son_pid, int *fd)
{
	int	i;
	int	status;

	i = 0;
	while (i <= data->meter->nbr_pipe) 
	{
		waitpid(son_pid[i], &status, 0);
		close_secure();        
		close_fd(fd[0]);
		close_fd(fd[1]);
		i++;
	}
	free(son_pid);
	close_fd(data->fd_pipe->fd_in);
	reset_fd(data);
	signal(SIGINT, SIG_DFL);
}
int	init_fd(t_data *data, int **fd, int **son_pid)
{
	data->sig_status = 1;
	data->fd_pipe->std_in = dup(STDIN_FILENO);
	if (data->fd_pipe->std_in == -1)
	{
        perror("dup STDIN_FILENO failed");
		return (1);
	}
	data->fd_pipe->std_out = dup(STDOUT_FILENO);
	if (data->fd_pipe->std_out == -1) 
	{
        perror("dup STDOUT_FILENO failed");
        close(data->fd_pipe->std_in);
		return (1);
    }
	*fd = ft_calloc(2, sizeof(int));
	if (*fd == NULL)
		return (1);
	*son_pid = ft_calloc(data->meter->nbr_pipe + 1, sizeof(int));
	if (*son_pid == NULL)
		return (1);
	return (0);
}
int start_process(t_data *data, int *son_pid, char *str)
{
	int i;

	i = 0;
	while (i <= data->meter->nbr_pipe)
	{
		if (data->output->h_doc[i] && *data->output->h_doc[i] != NULL)
			execute_heredoc(data, i);
		i++;
	}
	if (data->meter->nbr_pipe == 0) 
	{
		check_open_files(data, 0);
		free(son_pid);
		exec(data, data->command->cmd[0], data->command->arg[0], str);
		reset_fd(data);
	   return (0);
	}
	return (1);
}
int start_fork(int *fd, int *son_pid, int i)
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
	
	return (0);
}

void child_processus(t_data *data, int *fd, int i, char *str)
{
		printf("data->signal = %d\n", data->sig_status);

		check_open_files(data, i);
		if (!data->output->infile[i] && !data->output->h_doc[i]) 
		{
			 dup2(data->fd_pipe->fd_in, STDIN_FILENO);
			 close_fd(data->fd_pipe->fd_in);
		}  
		if (i != data->meter->nbr_pipe )
			{
				dup2(fd[1], STDOUT_FILENO);
				close_fd(fd[1]);
			}
		  close_fd(fd[0]);
		exec(data, data->command->cmd[i], data->command->arg[i], str);
}

void parent_processus(t_data *data, int *fd, int *i)
		{close_fd(fd[1]);
		data->fd_pipe->fd_in = fd[0];
		close_fd(fd[0]);
		*i+=1;
}

int my_pipe(t_data *data, char *str)
{
int i;
int *son_pid;
int *fd;

		data->sig_status = 1;
fd = NULL;
son_pid = NULL;
i = 0;
printf("data->signal = %d\n", data->sig_status);
if (init_fd(data, &fd, &son_pid))
	return (2);
if (!start_process(data, son_pid, str))
	return (2);
while (i <= data->meter->nbr_pipe)
{
	if (start_fork(fd, son_pid, i))
		return (2);
	if (son_pid[i] == 0) 
	{
		child_processus(data, fd, i, str);
		exit(127);
	} 
	else
		parent_processus(data, fd, &i);
}
end_process(data, son_pid, fd);
return (0);
}

