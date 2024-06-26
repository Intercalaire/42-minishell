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

static char		*environment_variable(t_data *data, char *str);
static int		ktq_utils(int in_qte_dble, int in_qte_sple);
static int		know_the_quote(char *str);
static	char	*make_the_char(t_data *data, char *str);

// char	*ft_strdup_2(t_data *data, const char *s)
// {
// 	char	*str = NULL;
// 	char	*env_value;
// 	int		i;
// 	int		j;
// 	char	*final_str;
// 	char *start_value;
// 	char *end_value;

// 	start_value = ft_calloc(ft_strlen(s) - ft_strlen(ft_strchr(s, '$')) , sizeof(char));
// 	if (!start_value)
// 		return (NULL);
// 	if (!s)
// 		return (NULL);
// 	env_value = NULL;
// 	if (str == NULL)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 		while (s[i] && s[i] != '$')
// 			start_value[j++] = s[i++];
// 		if (s[i] == '$')
// 		{
// 			env_value = environment_variable(data, (char *)s);
// 		}
// 		j = 0;
// 		while (s[i])
// 			end_value = ft_strdup(s + ft_strlen(s) + ft_strlen(env_value));
// 		if (env_value)
// 		{
// 			str = ft_strcat(str, start_value);
// 			str = ft_strcat(str, env_value);
// 			str = ft_strcat(str, end_value);
// 		}
// 		else
// 		{
// 			str = ft_strcat(str, start_value);
// 			str = ft_strcat(str, end_value);
// 	}
// 	printf("env_evalu = %s\n", env_value);
// 	str[j] = '\0';
// 	final_str = ft_trim_quote(str);
// 	return (final_str);
// }

// char	*ft_strdup_with_env(t_data *data, const char *s)
// {
// 	char	*result;
// 	char	*temp;
// 	int		i;
// 	int		len;

// 	if (!s)
// 		return (NULL);
// 	result = ft_calloc(1, sizeof(char)); // Initialise avec une chaîne vide
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 		{
// 			temp = environment_variable(data, (char *)&s[i]); // Cast pour éviter l'erreur de const
// 			len = strlen(temp);
// 			result = ft_realloc(result, strlen(result) + len + 1); // Réalloue pour la nouvelle taille
// 			if (!result)
// 				return (NULL);
// 			strcat(result, temp); // Ajoute la valeur de l'environnement à la chaîne
// 			i += data->len_env; // Saute les caractères de la variable d'environnement
// 		}
// 		else
// 		{
// 			len = strlen(result);
// 			result = ft_realloc(result, len + 2); // Réalloue pour ajouter un caractère
// 			if (!result)
// 				return (NULL);
// 			result[len] = s[i];
// 			result[len + 1] = '\0'; // Assure que la chaîne est toujours terminée par \0
// 			i++;
// 		}
// 	}
// 	result = ft_trim_quote(  );
// 	free(str);
// 	return (result);
// }
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
		if (str[i] == '$')
		{
			str = ft_strdup(environment_variable(data, str));
		}
		j += data->len_env;
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	result = ft_trim_quote(str);
	free(str);
	return (result);
}


static char	*environment_variable(t_data *data, char *str)
{
	char	*value;
	int		i;
	int		value_len;

	value = NULL;
	printf("know_the_quote = %d\n", know_the_quote(str));
	if (know_the_quote(str) == 1 || know_the_quote(str) == 0)
	{
		value = make_the_char(data, str);
		if (value == NULL)
			return (NULL);
		value_len = ft_strlen(value);
		printf("value = %s\n", value);
		i = search_env(data, value + 1);
		if (i == -1)
			return (" ");
		free(value);
		value = ft_strdup(data->env[i] + value_len);
	}
	else
		return (str);
	return (value);
}

static	char	*make_the_char(t_data *data, char *str)
{
	int i;
	int start;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	printf("i = %d\n", i);
	start = i;
	i++;
	while(str[i] && ft_isalnum(str[i]) == 1)
		i++;
	printf("i = %d\n", i);
	data->len_env = i - start;
	return (ft_strndup(str + start, i - start));
	
}

static int	know_the_quote(char *str)
{
	int	i;
	int	in_quote_simple;
	int	in_quote_double;

	i = 0;
	in_quote_simple = 0;
	in_quote_double = 0;
	if (str == NULL)
		return (2);
	while (str[i] && str[i] != '$')
	{
		if (in_quote_simple == 0 && str[i] == '\'' && in_quote_double == 0)
			in_quote_simple = 1;
		else if (in_quote_simple == 1 && str[i] == '\'')
			in_quote_simple = 0;
		else if (in_quote_double == 0 && str[i] == '"' && in_quote_simple == 0)
			in_quote_double = 1;
		else if (in_quote_double == 1 && str[i] == '"')
			in_quote_double = 0;
		i++;
	}
	return (ktq_utils(in_quote_double, in_quote_simple));
}

static int	ktq_utils(int in_qte_dble, int in_qte_sple)
{
	if (in_qte_dble == 1)
		return (1);
	if (in_qte_sple == 1)
		return (3);
	return (0);
}

// static char *handle_quoted_env_var(t_data *data, char *str, char quote_type)
// {
// 	char *env_var_name;
// 	char *value;
// 	char *trimmed_value;
// 	char *trimmed_str;

// 	env_var_name = str + 1;
// 	env_var_name[ft_strlen(env_var_name)-1] = '\0';
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

