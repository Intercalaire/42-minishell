/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:29:23 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/02 17:29:26 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static int	look_pipe_helper(t_data *data, char *str, int i);

int	look_pipe(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
	{
		ft_little_error_prog(data, str, PIPE);
		return (1);
	}
	if (look_pipe_helper(data, str, i) == 1)
		return (1);
	return (0);
}

static int	look_pipe_helper(t_data *data, char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				ft_little_error_prog(data, str, PIPE);
				return (1);
			}
		}
		i++;
	}
	if (i > 0 && str[i - 1] == '|')
	{
		ft_little_error_prog(data, str, PIPE);
		return (1);
	}
	return (0);
}

int	data_add_next(t_data *data, t_data *new_arg)
{
	t_data	*tmp;

	tmp = data;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_arg;
	new_arg->prev = tmp;
	return (0);
}

void	print_data(t_data *data)
{
	int			i;
	t_data		*tmp;

	tmp = data;
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

int	pars_pipe(t_data *data)
{
	t_data	*new_arg;
	char	*pipe_pos;
	t_data	*tmp;

	tmp = data;
	print_data(data);
	while (*data->arg)
	{
		pipe_pos = ft_strchr(*data->arg, '|');
		if (pipe_pos != NULL && *(data->arg + 1) != NULL)
		{
			new_arg = malloc(sizeof(t_data));
			if (!new_arg)
				ft_error_prog(data, *data->arg, "Error");
			new_arg->arg = ft_calloc(data->size, sizeof(char **));
			if (!data->arg)
				ft_error_prog(data, *data->arg, "Error");
			init_data(new_arg);
			new_arg->arg = data->arg + 1;
			data_add_next(data, new_arg);
		}
		data->arg++;
	}
	printf("data : %s\n", *data->arg);
	print_data(data);
	return (0);
}
