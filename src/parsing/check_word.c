/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:30:52 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/17 14:30:53 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

void	add_token(t_data *data, char *token)
{
	data->command->lign[data->count] = ft_strdup(token);
	if (ft_strchr(token, '|'))
		data->nbr_pipe++;
	printf("pipe ; %d\n", data->nbr_pipe);
	data->count++;
}
static int	len_ft_strtok(char *str)
{
	int		count;
	char	*token;

	count = 0;
	token = ft_strtok(str, " \t<>");
	while (token != NULL)
	{
		count++;
		token = ft_strtok(NULL, " \t<>");
	}
	return (count);
}
int	try_ft_strtok(t_data *data, char *str)
{
	char	*token;
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(str);
	data->count = len_ft_strtok(tmp);
	data->size = data->count;
	free(tmp);
	data->command->lign = ft_calloc((data->count + 1), sizeof(char **));
	if (!data->command->lign)
	{
		ft_little_error_prog(data, str, "Error");
		return (1);
	}
	token = ft_strtok(str, " \t<>");
	data->count = 0;
	while (token != NULL)
	{
		add_token(data, token);
		printf("lign : %s\n", data->command->lign[i]);
		token = ft_strtok(NULL, " \t<>");
		i++;
	}
	printf("%d\n", data->size);
	//after_ft_strtok(data, str);
	return (0);
}
