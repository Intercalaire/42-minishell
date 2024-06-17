/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:18:45 by hsolet            #+#    #+#             */
/*   Updated: 2024/06/17 09:18:48 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

int handle_heredoc(char *delimiter)
{
    char *line;
    char template[] = "/tmp/heredocXXXXXX";
    int fd = mkstemp(template);

    if (fd == -1)
    {
        perror("mkstemp");
        exit(EXIT_FAILURE);
    }

    while ((line = readline("")) != NULL)
    {
        // Check if the line matches the delimiter
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }

        // Write the line to the file
        write(fd, line, strlen(line));
        write(fd, "\n", 1);

        free(line);
    }

    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    return fd;
}