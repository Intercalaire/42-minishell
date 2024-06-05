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
#include "../../include/exec_test/minishell.h"
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

static void add_env(t_data *data, char *key, char *value)
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
    printf("env[%d] = %s\n", i, data->env[i]);

}

static void change_env(t_data *data, char *key, char *value)
{
    int		i;
    char	*new_env;

    i = search_env(data, key);
    new_env = ft_strdup(key);
    new_env = ft_strjoin(new_env, "=");
    new_env = ft_strjoin(new_env, value);
    free(data->env[i]);
    data->env[i] = new_env;
    printf("env[%d] = %s\n", i, data->env[i]);
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
int	ft_export(t_data *data)
{
    int		i;
    char	*key;
    char	*value;

    i = 0;


    while (data->command->arg[0][i])
    {
        if (!ft_strchr(data->command->arg[0][i], '='))
            {
                i++;
                continue ;
            }
        if (ft_strnstr(data->command->arg[0][i], "+=", ft_strlen(data->command->arg[0][i])) != NULL)
        {
            key = ft_strtok(data, data->command->arg[0][i], "+=");
            if (key)
                value = ft_strdup(data->command->arg[0][i] + ft_strlen(key) + 2);
            cat_env(data, key, value);
            i++;
            continue ;
        }
        else
        {    
            key = ft_strtok(data, data->command->arg[0][i], "=");
            if (key)
                value = ft_strdup(data->command->arg[0][i] + ft_strlen(key) + 1);
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