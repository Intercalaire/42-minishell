/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:36:06 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/15 11:54:37 by hsolet           ###   ########.fr       */
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
# include <string.h>

typedef struct s_command
{
	char					**lign;
	char					***arg;
	char					**cmd;
	struct s_command		*next;
	struct s_command		*prev;
}	t_command;

typedef struct s_data
{
	int					count;
	int					size;
	int				    nbr_pipe;
	int					exit_status;
	char				*env;
	t_command			*command;
}	t_data;


int try_ft_strtok(t_data *data, char *str);
void	init_data(t_data *data);
void ft_little_error_prog(t_data *data, char *str, char *msg);
void ft_error_prog(t_data *data, char *str, char *msg);
void ft_free_data(t_data *data, char *str);
void ft_free_strtab(char **tab);
void add_token(t_data *data, char *token);
int pars_pipe(t_data *data);
int	quote_verif(t_data *data,char *str);
int look_pipe(t_data *data, char *str);
int special_char(t_data *data, char *str);
void ft_end_error_prog(t_data *data, char *str, char *msg);
int	environment_variable(t_data *data, char *str);
int	error_code(t_data *data, char *str);
void after_ft_strtok(t_data *data, char *str);
void	ft_free_strarg(char ***tab);
char	*ft_trim_quote(char *str);
char	*ft_strtok(char *str, const char *delim);


# define PIPE "syntax error near unexpected token `|'"
# define TOKEN "syntax error near unexpected token"
# define QUOTE_SMP "syntax error near unexpected token `\''"
# define QUOTE_DBL "syntax error near unexpected token `\"'"

#endif
