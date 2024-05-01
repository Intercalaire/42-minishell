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

// static t_lst	*lst_new(char *content)
// {
// 	t_lst	*stack;

// 	stack = malloc(sizeof(t_lst));
// 	if (!stack)
// 		return (NULL);
// 	stack->content = content;
// 	stack->index = -1;
// 	stack->next = NULL;
// 	stack->prev = NULL;
// 	return (stack);
// }

// static void	lst_addfront(t_data *data, t_data *news)
// {
// 	if (!data || !news)
// 		return ;
// 	if (!(data))
// 	{
// 		data = news;
// 		(data)->prev = NULL;
// 		(data)->next = NULL;
// 		return ;
// 	}
// 	(data)->prev = news;
// 	news->next = data;
// 	data = news;
// 	news->prev = NULL;
// }

void add_token(t_data *data, char *token) {
    data->arg = (char **)ft_realloc(data->arg, (data->count + 1) * sizeof(char *));
    data->arg[data->count] = strdup(token);
    data->count++;
}

void try_ft_strtok(t_data *data, char *str)
{
    char *token;
    int i;

    (void)data;
    token = ft_strtok(str, " \t\"<|>'"); // " " is the delimiter
    i = 0;
    while (token != NULL)
    {
        add_token(data, token);
        if (i == 0)
            printf("Commande : %s\n", data->arg[i]);
        else
            printf("Arguments : %s\n", data->arg[i]);
        token = ft_strtok(NULL, " \t\"<|>'");
        i++;
    }
}
