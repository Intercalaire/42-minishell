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
/*
#include "../../include/parsing/minishell.h"

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

static int check_if_pipe(t_data *data)
{
	int i;

	i = 0;
	while (data->arg[i])
	{
		if (ft_strchr(data->arg[i], '|'))
			return (1);
		i++;
	}
	return (0);
}
//I want to put everything after "|" in a new structure
int pars_pipe(t_data *data)
{
	t_data	*new_arg;
	char	*pipe_pos;
	t_data	*tmp;

	tmp = data;
	while (tmp)
	{
		if (check_if_pipe(tmp) == 1)
		{
			pipe_pos = ft_strchr(*tmp->arg, '|');
			if (pipe_pos != NULL && *(tmp->arg + 1) != NULL)
			{
				new_arg = malloc(sizeof(t_data));
				if (!new_arg)
					ft_error_prog(data, *tmp->arg, "Error");
				new_arg->arg = ft_calloc(tmp->size, sizeof(char **));
				if (!new_arg->arg)
					ft_error_prog(data, *tmp->arg, "Error");
				init_data(new_arg);
				new_arg->arg = tmp->arg + 1;
				data_add_next(tmp, new_arg);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	pars_pipe2(t_data *data)
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
*/