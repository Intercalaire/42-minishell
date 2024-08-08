/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable_more_more_more_more_          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:09:08 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/05 08:09:10 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

static void	free_fsu(char *str, char *s, char *before);
static void	quote_fsu(char **s, char **before, char *str_str);
static void	in_function_fsu(t_data *data, char **s, char **env_str, char **str);

void	init_env_var(t_data *data)
{
	data->env_var->j = 0;
	data->env_var->k = 0;
	data->env_var->x = 0;
	data->env_var->z = 0;
	data->env_var->len_env_var = 0;
}

char	*ft_strdup_utils(t_data *data, const char *str_str, char *str, int i)
{
	char	*env_str;
	char	*s;
	char	*before;
	char	*final;

	init_env_var(data);
	env_str = NULL;
	if (str_str[0] != '$')
	{
		while (str_str[data->env_var->x] && str_str[data->env_var->x] != '$')
			data->env_var->x++;
	}
	s = ft_substr(str_str, data->env_var->x, i);
	before = ft_substr(str_str, 0, data->env_var->x);
	quote_fsu(&s, &before, (char *)str_str);
	str = ft_strdup_condition((char *)s, str, &data->env_var->j,
			&data->env_var->k);
	data->env_var->len_env_var = ft_strlen(s);
	while (data->env_var->k <= data->env_var->len_env_var
		&& data->env_var->k < i)
		in_function_fsu(data, &s, &env_str, &str);
	str[data->env_var->j] = '\0';
	final = ft_strjoin(before, str);
	free_fsu(str, s, before);
	return (ft_trim_quote(final));
}

static void	in_function_fsu(t_data *data, char **s, char **env_str, char **str)
{
	if ((*s)[data->env_var->k] == '$')
	{
		data->env_var->z = 0;
		*env_str = environment_variable(data, (char *)(*s + data->env_var->k),
				*s);
		if (*env_str)
		{
			while ((*env_str)[data->env_var->z])
			{
				(*str)[data->env_var->j++] = (*env_str)[data->env_var->z++];
			}
			data->env_var->k += data->len_env;
			free(*env_str);
			*env_str = NULL;
		}
		else
		{
			(*str)[data->env_var->j++] = (*s)[data->env_var->k++];
		}
	}
	else
		(*str)[data->env_var->j++] = (*s)[data->env_var->k++];
}

static void	quote_fsu(char **s, char **before, char *str_str)
{
	int	quote;

	quote = know_the_quote(*s);
	if (quote == 1)
	{
		if (*s)
			free(*s);
		if (*before)
			free(*before);
		*s = ft_strdup(str_str);
		*before = ft_strdup("");
	}
}

static void	free_fsu(char *str, char *s, char *before)
{
	if (str)
		free(str);
	if (s)
		free(s);
	if (before)
		free(before);
}
