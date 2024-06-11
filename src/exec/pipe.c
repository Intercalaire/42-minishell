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
#include "../../include/exec_test/minishell.h"

int my_pipe(t_data *data)
{
int i;
int *son_pid;
int tmp_fd;
char *filename;

i = 0;
if (data->nbr_pipe == 0) 
{
    // If there is no pipe, just execute the command
    exec(data, data->command->cmd[0], data->command->arg[0]);
    return 0;
}
while (i < data->nbr_pipe)
{
    son_pid[i] = fork();
    if (son_pid[i] == -1)
        erreur();
    else if (son_pid[i] == 0) {
        filename = ft_strdup("tmp.txt");
		if (filename == NULL)
			erreur();
        if (i > 0) {
            tmp_fd = open(filename, O_RDONLY);
            if (tmp_fd == -1)
                erreur();
            dup2(tmp_fd, STDIN_FILENO);
            close(tmp_fd);
        }
        tmp_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (tmp_fd == -1)
            erreur();
        dup2(tmp_fd, STDOUT_FILENO);
        free(filename);
        exec(data, data->command->cmd[i], data->command->arg[i]); // Use your custom function here
        close(tmp_fd);
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL); // Wait for child process to finish
    }
    i++;
}
unlink(filename); // Delete the file
return (0);
}