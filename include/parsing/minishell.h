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

extern int g_sig;

typedef struct s_command
{
char	**lign;
char	***arg;
char	**cmd;
}	t_command;

typedef struct s_meter
{
int		nbr_arg;
int		nbr_pipe;
int		nbr_outfile;
int		nbr_h_doc;
int		nbr_infile;
int		nbr_outfile_append;
int		count_outfile;
int		count_h_doc;
int		count_infile;
int		count_outfile_append;
}	t_meter;

typedef struct s_output
{
int		*append;
int		*here_d;
int		sign;
char	***outfile;
char	***outfile_append;
char	***infile;
char	***h_doc;
}	t_output;

typedef struct s_data
{
int			count;
int			size;
int			nbr_pipe;
int 		nbr_arg;
int			exit_status;
int 		in_quote;
char		**env;
int			len_env;
int         sig_status;
t_output	*output;
t_meter		*meter;
t_command	*command;
}	t_data;


//with ft_strtok
int 	try_ft_strtok(t_data *data, char *str);
char	*ft_strtok(char *str, const char *delim);
char	*ft_split_delim(char *str);
int		remove_arg_strtab(t_data *data);

//parsing
int 	pars_pipe(t_data *data);
int		quote_verif(t_data *data,char *str);
int 	look_pipe(t_data *data, char *str);
int 	special_char(t_data *data, char *str);
void	remove_end_space(char *str);
int		handle_args(t_data *data, int *i, int *y, int *z);
void	count_args(t_data *data, int i);

//environment_variable
int		ktq_utils(int in_qte_dble, int in_qte_sple);
char	*ft_strdup_2(t_data *data, const char *s);

//utils
void	count_pipes_outside_quotes(t_data *data, const char *str);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
int		init_zero(t_data *data);

//free
void 	ft_little_error_prog(t_data *data, char *str, char *msg);
void 	ft_error_prog(t_data *data, char *str, char *msg);
void 	ft_free_data(t_data *data, char *str);
void 	ft_free_strtab(char **tab);
void 	ft_end_error_prog(t_data *data, char *str, char *msg);
int		error_code(t_data *data, char *str);
void	ft_free_strarg(char ***tab);
void	ft_little_error_prog_no_msg(t_data *data, char *str);

//init
int		init_data(t_data *data);

//exec
int		ft_export(t_data *data, char **arg);
int		exec(t_data *data, char *cmd, char **arg, char *str);
void		path(t_data *data, char *cmd, char **arg);
int		print_env(t_data *data, char **arg);
int		echo(char **arg);
int		cd(t_data *data, char **arg);
int		search_env(t_data *data, char *str);
int		my_pipe(t_data *data, char *str);
int		ft_unset(t_data *data, char **arg);
int		pwd(void);
void	cpy_env(t_data *data, char **environnement);
void	change_env(t_data *data, char *key, char *value);
void	add_env(t_data *data, char *key, char *value);
void	exit_shell(t_data *data, char *str, char **arg);
void	ft_sig(t_data *data);
char    **cpy_envir(char **env);
void    cat_env(t_data *data, char *key, char *value);
char    **bubble_sort(char **arr, int n);

//output
int		verif_output(t_data *data, int *y, char *str);
int		verif_lign(t_data *data, char *str);
int		init_global(t_data *data);
int		count_output(t_data *data, char *str, int y);
int		count_all(t_data *data, int *y, int i);

//output_init
int		outfile(t_data *data, int *y, char *str);
int		outfile_append(t_data *data, int *y, char *str);
int		infile(t_data *data, int *y, char *str);
int		h_doc(t_data *data, int *y, char *str);

# define PIPE "syntax error near unexpected token `|'"
# define TOKEN "syntax error near unexpected token"
# define QUOTE_SMP "syntax error near unexpected token `\''"
# define QUOTE_DBL "syntax error near unexpected token `\"'"

#endif