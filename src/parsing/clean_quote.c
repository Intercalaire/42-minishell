/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:47:51 by vgodart           #+#    #+#             */
/*   Updated: 2024/06/13 16:47:53 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static void	print_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->command->cmd[i])
	{
		printf("cmd2[%d] : %s\n", i, data->command->cmd[i]);
		i++;
	}
}

static void	print_arg(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	if (data->command->arg != NULL)
	{
		while (data->command->arg[i])
		{
			y = 0;
			if (data->command->arg[i] != NULL)
			{
				while (data->command->arg[i][y])
				{
					printf("arg2[%d][%d] : %s\n", i, y, data->command->arg[i][y]);
					y++;
				}
			}
			i++;
		}
	}
}

char *align_and_clean_quotes(t_data *data)
{
	char *result = NULL;
	char *temp;
	int i = 0;

	printf("JE RENTRE\n");
	while(data->command->cmd[i])
	{
		temp = ft_trim_quote(data->command->cmd[i]);
		if (result == NULL)
		{
			result = malloc(strlen(temp) + 1);
			strcpy(result, temp);
		}
		else
		{
			result = realloc(result, strlen(result) + strlen(temp) + 1);
			strcat(result, temp);
		}
		free(temp);
		i++;
	}

	print_cmd(data);
	print_arg(data);
	return result;
}