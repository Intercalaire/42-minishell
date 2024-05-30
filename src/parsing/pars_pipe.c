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
/*
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
	while (data->command->lign[i])
	{
		if (ft_strchr(data->command->lign[i], '|'))
			return (1);
		i++;
	}
	return (0);
}

//il faut : mettre pour la premier fois quand ya pas de pipe, trouver des malloc pour chaque pipe
int pars_pipe(t_data *data)
{
	int	i;
	int y;

	i = 0;
	y = 0;
	data->command->cmd = ft_calloc(data->nbr_pipe + 1, sizeof(char **));
	if (!data->command->cmd)
		ft_error_prog(data, *data->command->cmd, "Error");
	while(data->command->lign[i])
	{
		if (check_if_pipe(data) == 1)
		{
			data->command->arg = malloc(sizeof(t_data));
			if (!data->command->arg)
				ft_error_prog(data, *data->command->arg, "Error");
			data->command->arg = ft_calloc(data->size, sizeof(char **));
			if (!data->command->arg)
				ft_error_prog(data, *data->command->arg, "Error");
			data->command->arg = data->command->arg + 1;
			data_add_next(data, data);
		}
		i++;
	}
}*/


/*
//I want to put everything after "|" in a new structure
int	pars_pipe2(t_data *data)
{
    t_data	*new_arg;
    char	*pipe_pos;
    t_data	*tmp;
    int		i;

    tmp = data;
    i = 0;
    while (data->command->arg[i])
    {
        pipe_pos = ft_strchr(*data->command->arg[i], '|');
        if (pipe_pos != NULL && *data->command->arg[i + 1] != NULL)
        {
            new_arg = malloc(sizeof(t_data));
            if (!new_arg)
                ft_error_prog(data, *data->command->arg[i], "Error");
            new_arg->command->arg = ft_calloc(data->size, sizeof(char **));
            if (!new_arg->command->arg)
                ft_error_prog(data, *data->command->arg[i], "Error");
            new_arg->command->cmd = ft_calloc(data->size, sizeof(char *));
            if (!new_arg->command->cmd)
                ft_error_prog(data, *data->command->arg[i], "Error");
            if (i == 0 || *pipe_pos == '|')
            {
                new_arg->command->cmd[i] = ft_strdup(*data->command->arg[i]);
            }
            else
            {
                new_arg->command->arg[i] = ft_strdup(*data->command->arg[i]);
            }
        }
        i++;
    }
}*/
/*
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
}*/