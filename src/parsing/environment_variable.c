/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:28:19 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/07 14:28:21 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

// static char	*environment_variable(t_data *data, char *str);
// static char	*handle_mid_string_env_var(t_data *data, char *str);
// static char *handle_quoted_env_var(t_data *data, char *str, char quote_type);
// static char *handle_simple_env_var(t_data *data, char *str);

char	*ft_strdup_2(t_data *data, const char *s)
{
	int		i;
	int		j;

	char	*str;
	char	*result;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	str = ft_calloc((i + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	//str = ft_strdup(environment_variable(data, str));
	result = ft_trim_quote(str);
	free(str);
	(void)data;
	return (result);
}

// static char	*handle_mid_string_env_var(t_data *data, char *str)
// {
//     char	*value;
//     int		i;
//     char	*env_var_name;
//     char	*new_str;
//     char	*prefix;
//     char	*suffix;

//     char *dollar_pos = strchr(str, '$');
//     while (dollar_pos != NULL)
// 	{
//         prefix = strndup(str, dollar_pos - str);
//         env_var_name = dollar_pos + 1;
//         suffix = strchr(env_var_name, ' ');
//         if (suffix != NULL) {
//             env_var_name = strndup(env_var_name, suffix - env_var_name);
//             suffix++;
//         }
//         i = search_env(data, env_var_name);
//         if (i != -1)
// 		{
//             value = ft_strdup(data->env[i] + ft_strlen(env_var_name) + 1);
//             if (value == NULL)
//                 return (NULL);
//             new_str = malloc(strlen(prefix) + strlen(value) + (suffix != NULL ? strlen(suffix) : 0) + 1);
//             strcpy(new_str, prefix);
//             strcat(new_str, value);
//             if (suffix != NULL)
//                 strcat(new_str, suffix);
//             free(str);
//             str = new_str;
//         }
//         dollar_pos = strchr(str, '$');
//     }
//     return (str);
// }

// static char *handle_quoted_env_var(t_data *data, char *str, char quote_type)
// {
// 	char *env_var_name;
// 	char *value;
// 	char *trimmed_value;
// 	char *trimmed_str;

// 	env_var_name = str + 1;
// 	env_var_name[strlen(env_var_name)-1] = '\0';
// 	while (env_var_name[0] == '\"' || env_var_name[0] == '\'')
// 	{
// 		env_var_name++;
// 		env_var_name[strlen(env_var_name)-1] = '\0';
// 	}
// 	if (env_var_name[0] == '$')
// 	{
// 		if (quote_type == '\"' || quote_type == '\'')
// 			env_var_name++;
// 		int i = search_env(data, env_var_name);
// 		if (i != -1)
// 		{
// 			if (quote_type == '\"')
// 			{
// 				value = ft_strdup(data->env[i] + ft_strlen(env_var_name) + 1);
// 				if (value == NULL)
// 					return (NULL);
// 				trimmed_value = (str[0] == '\"' && str[strlen(str)-1] == '\"') ? value : ft_trim_quote(value);
// 				if (value != trimmed_value)
// 					free(value);
// 				return trimmed_value;
// 			}
// 			else if (quote_type == '\'')
// 			{
// 				value = ft_strdup(env_var_name - 1);
// 				trimmed_value = (str[0] == '\'' && str[strlen(str)-1] == '\'') ? value : ft_trim_quote(value);
// 				if (value != trimmed_value)
// 					free(value);
// 				return trimmed_value;
// 			}
// 		}
// 	}
// 	trimmed_str = ft_trim_quote(str);
// 	return trimmed_str;
// }

// static char *handle_simple_env_var(t_data *data, char *str)
// {
// 	char *trimmed_str;
// 	char *trimmed_value;
// 	char *value;
// 	int i;
	
// 	i = search_env(data, str + 1);
// 	if (i != -1)
// 	{
// 		value = ft_strdup(data->env[i] + ft_strlen(str + 1) + 1);
// 		if (value == NULL)
// 			return (NULL);
// 		trimmed_value = (str[0] == '$' && str[strlen(str)-1] == '$') ? value : ft_trim_quote(value);
// 		if (value != trimmed_value)
// 			free(value);
// 		return trimmed_value;
// 	}
// 	trimmed_str = ft_trim_quote(str);
// 	return trimmed_str;
// }

// static char	*environment_variable(t_data *data, char *str)
// {
// 	if (str[0] == '\"' || str[0] == '\'')
// 	{
// 		return handle_quoted_env_var(data, str, str[0]);
// 	}
// 	else if (str[0] == '$')
// 	{
// 		return handle_simple_env_var(data, str);
// 	}
// 	else
// 	{
// 		return handle_mid_string_env_var(data, str);
// 	}
// }