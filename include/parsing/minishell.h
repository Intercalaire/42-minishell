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
	int					size;
}	t_data;


void try_ft_strtok(t_data *data, char *str);
void	init_data(t_data *data);
void ft_little_error_prog(t_data *data, char *str, char *msg);
void ft_error_prog(t_data *data, char *str, char *msg);
void ft_free_data(t_data *data, char *str);
void ft_free_strtab(char **tab);
void add_token(t_data *data, char *token);
int pars_pipe(t_data *data);
int	quote_verif(t_data *data,char *str);
int look_pipe(t_data *data, char *str);

#endif