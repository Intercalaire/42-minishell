/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:16:19 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/30 15:16:27 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"
// ' ' '\t' '"' '<' '|' '>' '\''

static char *ft_strtok(char *str, const char *delim) {
    static char *src = NULL;
    char *p;
	char *ret;

	ret = 0;
	p = 0;
    if(str != NULL)
        src = str;
    if(src == NULL)
        return NULL;
    while (ft_strchr(delim, *src))
        src++;
    p = src;
    while (*p != '\0' && !ft_strchr(delim, *p))
        p++;
    if (*p != '\0') 
	{
        *p = 0;
        ret = src;
        src = ++p;
    }
	else if (*src != '\0')
	{
        ret = src;
        src = NULL;
    }
    return ret;
}


void try_ft_strtok(char *str) {
    char *token;

    token = ft_strtok(str, " \t\"<|>'"); // " " is the delimiter
    while (token != NULL) {
        printf("%s\n", token);
        token = ft_strtok(NULL, " \t\"<|>'");
    }
}
