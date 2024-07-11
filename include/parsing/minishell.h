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
int     fd;
char	***outfile;
char	***outfile_append;
char	***infile;
char	***h_doc;
}	t_output;

typedef struct s_fd_pipe
{
    int std_in;
    int std_out;
    int fd_in;
} t_fd_pipe;

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
t_fd_pipe	*fd_pipe;
}	t_data;

//with ft_strtok
int 	try_ft_strtok(t_data *data, char *str);
char	*ft_strtok(char *str, const char *delim);
char	*ft_split_delim(char *str);

//parsing
int 	pars_pipe(t_data *data);
int		quote_verif(t_data *data,char *str);
int 	look_pipe(t_data *data, char *str);
int 	special_char(t_data *data, char *str);
int     remove_end_space(t_data *data, char *str);
int		handle_args(t_data *data, int *i, int *y, int *z);
void	count_args(t_data *data, int i);
int		look_out(t_data *data, char *str);
int		know_the_delim_quote(char *str);

//environment_variable
int		ktq_utils(int in_qte_dble, int in_qte_sple);
char	*ft_strdup_2(t_data *data, const char *s);
char	*env_var_utils(t_data *data, char *value, int quote);
char	*char_dollar_stop(char *value);
int		check_dollar_stop(char *value);
int		ft_ischar_no_quotes(int c);
char	*ft_strdup_condition(char *s, char *str, int *j, int *k);
int		ft_find_char(char *str, char c);

//utils
void	count_pipes_outside_quotes(t_data *data, const char *str);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
int		init_zero(t_data *data);

//free
void	ft_little_error_prog(t_data *data, char *str, char *msg, char token);
void	ft_little_error_prog_quote(t_data *data, char *str, char *msg);
void 	ft_error_prog(t_data *data, char *str, char *msg);
void 	ft_free_data(t_data *data, char *str);
void 	ft_free_strtab(char **tab);
void 	ft_end_error_prog(t_data *data, char *str, char *msg);
void	ft_free_strarg(char ***tab);
void	ft_little_error_prog_no_msg(t_data *data, char *str);

//init
int		init_data(t_data *data);
void	init_int_values(int *i, int *j, int *in_quotes);

//exec
int		ft_export(t_data *data, char **arg);
int		exec(t_data *data, char *cmd, char **arg, char *str);
void	path(t_data *data, char *cmd, char **arg, char *str);
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
int		ft_sig(t_data *data);
char    **cpy_envir(char **env);
void    cat_env(t_data *data, char *key, char *value);
char    **bubble_sort(char **arr, int n);
void	execution(t_data *data, char *cmd, char **args, char *full_path);
char	**create_args(char *cmd, char **arg);
char	*var_path(t_data *data, char *cmd);
int    create_outfiles(t_data *data, int i);
int    create_outfiles_append(t_data *data, int i);
int    create_infiles(t_data *data, int i);
int    create_infiles_heredoc(t_data *data, int i);
int     close_fd(int fd);

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
# define OUT "syntax error near unexpected token `newline'"

#endif