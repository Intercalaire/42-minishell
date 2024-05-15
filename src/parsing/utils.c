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
    char        *p;
	char        *ret;

    ret = 0;
	p = 0;
    if (str != NULL)
        src = str;
    if (src == NULL)
        return NULL;
    while (ft_strchr(delim, *src) && *src != '\0')
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
    return (ret);
}

static int len_ft_strtok(char *str)
{
    int count;
    char *token;

    count = 0;
    token = ft_strtok(str, " \t\"<>'");
    while (token != NULL)
    {
        count++;
        token = ft_strtok(NULL , " \t\"<>'");
    }
    return (count);
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

void add_token(t_data *data, char *token)
{
    data->command->arg[data->count] = ft_strdup(token);
    data->count++;
}

int try_ft_strtok(t_data *data, char *str)
{
    char *token;
    int i;
    char    *tmp;

    i = 0;
    tmp = ft_strdup(str);
    data->count = len_ft_strtok(tmp);
    data->size = data->count;
    free(tmp);
    data->command->arg = ft_calloc((data->count + 1) , sizeof(char **));
    if (!data->command->arg)
    {
        ft_little_error_prog(data, str, "Error");
        return(1);
    }
    token = ft_strtok(str, " \t\"<>'");
    data->count = 0;
    while (token != NULL)
    {
        add_token(data, token);
        //printf("arg : %s\n", data->command->arg[i]);
        token = ft_strtok(NULL, " \t\"<>'");
        i++;
    }
    after_ft_strtok(data, str);
    return (0);
}

void	print_data(t_data *data)
{
	int			i;
	t_command		*tmp;

	tmp = data->command;
	while (tmp)
	{
		i = 0;
		while (tmp->arg[i])
		{
			printf("arg[%d] : %s\n", i, tmp->arg[i]);
			i++;
		}
		tmp = tmp->next;
	}
}


void after_ft_strtok(t_data *data, char *str)
{
    int i;

    i = 0;
    if (data->command->arg)
        data->command->cmd = data->command->arg[0];
    while(data->command->arg[i])
    {
        if (*data->command->arg[i] == '|')
                data->command->next->cmd = *data->command->arg;
         i++;
    }
    (void)str;
    printf("cmd : %s\n", data->command->cmd);
    print_data(data);
}

