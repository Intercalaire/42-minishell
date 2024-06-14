/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:10:31 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/30 12:04:17 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"
static void copy_env(t_data *data)
{
    int i = 0;
    char **new_env;

    while (data->env[i])
        i++;
    new_env = ft_calloc((i + 2), sizeof(char *));
    if (!new_env)
        return ;
    i = 0;
    while (data->env[i]) 
    {
        new_env[i] = ft_strdup(data->env[i]);
        free(data->env[i]);
        i++;
    }
    free(data->env);
    data->env = new_env;
}

void add_env(t_data *data, char *key, char *value)
{
    int		i;
    char	*new_env;
    char    *tmp;

    i = 0;
    copy_env(data);
    while (data->env[i])
        i++;
    new_env = ft_strdup(key);
    tmp = ft_strjoin(new_env, "=");
    free(new_env);
    new_env = ft_strjoin(tmp, value);
    free(tmp);
    data->env[i] = new_env;
    data->env[i + 1] = NULL;


}

void change_env(t_data *data, char *key, char *value)
{
    int		i;
    char	*new_env;

    i = search_env(data, key);
    new_env = ft_strdup(key);
    new_env = ft_strjoin(new_env, "=");
    new_env = ft_strjoin(new_env, value);
    free(data->env[i]);
    data->env[i] = new_env;

}

static void cat_env(t_data *data, char *key, char *value)
{
    int		i;
    char	*new_env;
    char	*tmp;

    i = search_env(data, key);
    tmp = ft_strdup(data->env[i]);
    new_env = ft_strjoin(tmp, value);
    free(data->env[i]);
    data->env[i] = new_env;
    free(tmp);
    free(new_env);
}
static char **bubble_sort(char **arr, int n)
{
    int i = 0;
    int j = 0;
    char *temp;

    while (i < n - 1)
    {
        j = 0;
        while (j < n - i - 1)
        {
            if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j + 1])) > 0)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    return (arr);
}

static char **cpy_envir(char **env)
{
    int i = 0;
    int env_len = 0;
    char **new_env;

    while (env[env_len])
        env_len++;
    new_env = ft_calloc((env_len + 1), sizeof(char *));
    if (!new_env)
        return NULL;

    while (i < env_len)
    {
        new_env[i] = ft_strdup(env[i]);
        i++;
    }
    new_env[i] = NULL;

    return (new_env);
}

int	ft_export(t_data *data, char **arg)
{
    int		i;
    char	*key;
    char	*value;
    int     env_len;
    char **new_env;

    i = 0;

    if (!arg)
    {
        env_len = 0;
        while (data->env[env_len])
            env_len++;
        new_env = cpy_envir(data->env);
        bubble_sort(new_env, env_len);
        while (new_env[i])
        {
            printf("declare -x %s\n", new_env[i]);
            i++;
        }
        return (0);
    }

    while (arg[i])
    {
        if (!ft_strchr(arg[i], '='))
            {
                i++;
                continue ;
            }
        if (ft_strnstr(arg[i], "+=", ft_strlen(arg[i])) != NULL)
        {
            key = ft_strtok(data, arg[i], "+=");
            if (key)
                value = ft_strdup(arg[i] + ft_strlen(key) + 2);
            cat_env(data, key, value);
            i++;
            continue ;
        }
        else
        {    
            key = ft_strtok(data, arg[i], "=");
            if (key)
                value = ft_strdup(arg[i] + ft_strlen(key) + 1);
            if (!key || !value)
                return (ft_putstr_fd("Usage: export NAME=VALUE\n", 1));
            if (search_env(data, key) == -1)
                add_env(data, key, value);
            else
                change_env(data, key, value);
            i++;
        }
    }
    free (key);
    free (value);
    return (0);
}