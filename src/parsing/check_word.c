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

static int	process_tokens(t_data *data, char *str);
static int	initialize_data(t_data *data, char *str);
static int	len_ft_strtok(char *str);
static int	add_token(t_data *data, char *token);

static int	add_token(t_data *data, char *token)
{
	data->command->lign[data->count] = ft_strdup(token);
	if (!data->command->lign[data->count])
		return (2);
	data->count++;
	return (0);
}

static int	len_ft_strtok(char *str)
{
	int		count;
	char	*token;

	count = 0;
	token = ft_strtok(str, " \t\n\v\r\f");
	while (token != NULL)
	{
		count++;
		free(token);
		token = ft_strtok(NULL, " \t\n\v\r\f");
	}
	if (token)
		free(token);
	return (count);
}

static int	initialize_data(t_data *data, char *str)
{
	char	*tmp;

	tmp = ft_strdup(str);
	if (!tmp)
		return (2);
	data->count = len_ft_strtok(tmp);
	data->size = data->count;
	free(tmp);
	data->command->lign = ft_calloc((data->count + 1), sizeof(char **));
	if (!data->command->lign)
		return (2);
	return (0);
}

static int	process_tokens(t_data *data, char *str)
{
	char	*token;
	int		i;

	i = 0;
	count_pipes_outside_quotes(data, str);
	token = ft_strtok(str, " \t\n\v\r\f");
	if (!token)
		return (2);
	data->count = 0;
	while (token != NULL)
	{
		add_token(data, token);
		free(token);
		printf("lign : %s\n", data->command->lign[i]);
		token = ft_strtok(NULL, " \t\n\v\r\f");
		if (!token)
			return (2);
		i++;
	}
	free(token);
	return (0);
}

int	try_ft_strtok(t_data *data, char *str)
{
	str = ft_split_delim(str);
	if (!str)
		return (2);
	if (initialize_data(data, str) == 2)
		return (2);
	process_tokens(data, str);
	printf("%d\n", data->size);
	printf("pipe ; %d\n", data->nbr_pipe);
	return (0);
}
