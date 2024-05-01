/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:36:06 by vgodart           #+#    #+#             */
/*   Updated: 2024/04/30 12:36:07 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char				**arg;
	struct s_data		*next;
	struct s_data		*prev;
	int					count;
}	t_data;

typedef struct s_lst
{
	char				*content;
	int				index;
	struct s_lst	*next;
	struct s_lst	*prev;
}				t_lst;

void try_ft_strtok(t_data *data, char *str);
void	init_data(t_data *data);

#endif