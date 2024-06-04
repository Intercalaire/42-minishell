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

#include "../../include/exec_test/minishell.h"
// ' ' '\t' '"' '<' '|' '>' '\''

void count_pipes_outside_quotes(t_data *data, const char *str)
{
    int in_single_quotes = 0;
    int in_double_quotes = 0;
    int i = 0;

    data->nbr_pipe = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\"' && !in_single_quotes)
            in_double_quotes = !in_double_quotes;
        else if (str[i] == '\'' && !in_double_quotes)
            in_single_quotes = !in_single_quotes;
        else if (str[i] == '|' && !in_single_quotes && !in_double_quotes)
            data->nbr_pipe++;
        i++;
    }
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

// void	print_data(t_data *data)
// {
// 	int			i;
// 	t_command		*tmp;

// 	tmp = data->command;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->arg[i])
// 		{
// 			printf("arg[%d] : %s\n", i, tmp->arg[i]);
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }
// //count pipe    ->    data->command->arg = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
// //              ->    data->command->arg[0 -> nbr_pipe + 1] = ft_calloc(data->nbr_arg_cmd + 1, sizeof(char *));
// //              ->    data->command->arg[0 -> nbr_pipe + 1][0   ->   nbr_arg] = ft_calloc(ft_strlen(mot), sizeof(char));

// void    after_ft_strtok(t_data *data)
// {
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     data->command->arg = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
//     if (!data->command->arg)
//         ft_error_prog(data, NULL, "Error");
//     data->command->cmd = ft_calloc(data->nbr_pipe + 1, sizeof(char *));
//     if (!data->command->cmd)
//         ft_error_prog(data, NULL, "Error");
//     while(i < data->nbr_pipe + 1)
//     {
//         data->command->arg[i] = ft_calloc(data->size, sizeof(char *));
//         if (!data->command->arg[i])
//             ft_error_prog(data, NULL, "Error");
//         while(data->command->lign[j])
//         {
//             data->command->arg[i][j] = ft_strdup(data->command->lign[j]);
//             data->command->cmd[i] = ft_strdup(data->command->lign[i]);
//         }
//         i++;
//     }

// }









// void after_ft_strtok_test(t_data *data, char *str)
// {
//     int i;
//     int j;
//     int k;

//     i = 0;
//     j = 0;
//     k = 0;
//     data->command->cmd = ft_calloc(data->size, sizeof(char *));
//     data->command->arg = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
//     if (data->command->lign)
//     {
//         data->command->cmd[k] = data->command->lign[i];
//         i++;
//         k++;
//     }
//     while(data->command->lign[i])
//     {
//         if (*data->command->lign[i] == '|' && data->command->lign[i] != ""|"")
//         {
//                 data->command->cmd[k] = *data->command->lign[i];
//                 k++;
//         }
//         else
//         {
//             data->command->arg[i][j][] = *data->command->lign[i];
//             j++;
//         }
//         i++;
//     }
//     (void)str;
//     //printf("cmd : %s\n", data->command->cmd);
//     //print_data(data);
// }

