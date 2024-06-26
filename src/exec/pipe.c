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

char *get_env_value(t_data *data, char *varName)
{
    int index = search_env(data, varName);
    if (index == -1) return NULL; // La variable d'environnement n'a pas été trouvée

    char *entry = data->env[index];
    char *value = strchr(entry, '='); // Trouver le signe '='
    if (!value) return NULL; // Format invalide, pas de valeur

    return value + 1; // Retourner la valeur (après le signe '=')
}

char *expand_env_vars(t_data *data, char *line)
{
    // Étape 1 : Calculer la taille nécessaire
    int size_needed = 1; // Pour le caractère de fin de chaîne '\0'
    for (char *ptr = line; *ptr; ptr++)
    {
        if (*ptr == '$')
        {
            // Trouver la fin du nom de la variable
            char *end = ptr + 1;
            while (isalnum(*end) || *end == '_') end++;

            // Calculer la taille du nom de la variable
            char varName[256];
            int len = end - (ptr + 1);
            strncpy(varName, ptr + 1, len);
            varName[len] = '\0';

            // Obtenir la valeur de la variable d'environnement
            char *value = get_env_value(data, varName);
            if (value)
            {
                size_needed += strlen(value); // Ajouter la taille de la valeur
            }

            ptr = end - 1; // Avancer le pointeur
        }
        else
        {
            size_needed++; // Pour le caractère courant
        }
    }

    // Étape 2 : Allouer suffisamment de mémoire
    char *result = malloc(size_needed);
    if (!result) return NULL;

    // Étape 3 : Construire la chaîne avec les valeurs des variables
    char *temp = result;
    for (char *ptr = line; *ptr; ptr++)
    {
        if (*ptr == '$')
        {
            char *end = ptr + 1;
            while (isalnum(*end) || *end == '_') end++;

            int len = end - (ptr + 1);
            char varName[256];
            strncpy(varName, ptr + 1, len);
            varName[len] = '\0';

            char *value = get_env_value(data, varName);
            if (value)
            {
                strncpy(temp, value, size_needed - (temp - result));
                temp += strlen(value);
            }

            ptr = end - 1;
        }
        else
        {
            *temp++ = *ptr;
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
            if (g_sig == SIGINT)
            {
                free(line);
                close(fd); 
                unlink(tmpfile);
                free(tmpfile);
                return;
            }

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
    int j;
    int infd;

    j = 0;
    while (data->output->h_doc[i][j] != NULL) 
        j++;
    if (data->output->h_doc[i][j - 1])
    {
        tmpfile = ft_strjoin("tmp_files/",data->output->h_doc[i][j - 1]);
        infd = open(tmpfile, O_RDONLY | O_CREAT, 0644);
        if (infd < 0) 
        {
            perror("open_heredoc");
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
   //close(original_stdin);

int original_stdout = dup(STDOUT_FILENO);
if (original_stdout == -1) {
    perror("dup");
    return 1;
}
//close(original_stdout);

nbr_pipe = 0;
while (data->command->cmd[nbr_pipe + 1])
    nbr_pipe++;
son_pid = ft_calloc(nbr_pipe + 1, sizeof(int));
if (son_pid == NULL)
    return (1);
// if (nbr_pipe == 0) 
// {
//    if (data->output->h_doc[0] && *data->output->h_doc[0] != NULL)
//    {
//        execute_heredoc(data, 0);
//        create_infiles_heredoc(data, 0);
//    }
//    if (data->output->infile[0]) 
//        create_infiles(data, 0);
//    if (data->output->outfile[0]) 
//        create_outfiles(data, 0);
//    if (data->output->outfile_append[0]) 
//        create_outfiles_append(data, 0);
//    free(son_pid);
//    exec(data, data->command->cmd[0], data->command->arg[0], str);
//    dup2(original_stdin, STDIN_FILENO);
//    close(original_stdin);
//    dup2(original_stdout, STDOUT_FILENO);
//    close(original_stdout);
//    signal(SIGINT, SIG_DFL);
//    //close_secure();
//    return (0);
// }
int fd[2];

while (i <= nbr_pipe)
{
    if (data->output->h_doc[i] && *data->output->h_doc[i] != NULL)
        execute_heredoc(data, i);
    i++;
}
i = 0;
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
            printf("dans le if\n");
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
            {
                dup2(fd[1], STDOUT_FILENO);
                close_fd(fd[1]);
            }
          close_fd(fd[0]);
        exec(data, data->command->cmd[i], data->command->arg[i], str);
        exit(127);
    } 
    else
    {
        close_fd(fd[1]);
          if (i != 0)
                close_fd(fd_in);
        fd_in = fd[0];
        close_fd(fd[0]);
        i++;
    }
}
i = 0;
while (i <= nbr_pipe) 
{
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
        signal(SIGINT, SIG_DFL);
return 0;
}
