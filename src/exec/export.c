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
        i++;
    }
    ft_free_strtab(data->env);
    cpy_env(data, new_env);
    ft_free_strtab(new_env);
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
    if (value)
    {
        tmp = ft_strjoin(new_env, "=");
        free(new_env);
        new_env = ft_strjoin(tmp, value);
        free(tmp);
    }
    free(data->env[i - 1]);
    data->env[i - 1] = ft_strdup(new_env);
    free(data->env[i]);
    data->env[i] = NULL;
    free(new_env);
}

void change_env(t_data *data, char *key, char *value)
{
    int		i;
    char	*new_env;
    char    *tmp;

    i = search_env(data, key);
    if (i == -1) {
        printf("Variable '%s' not found in environment\n", key);
        return;
    }
    new_env = ft_strdup(key);
    tmp = ft_strjoin(new_env, "=");
    free(new_env);
    new_env = ft_strdup(tmp);
    free(tmp);
    tmp = ft_strjoin(new_env, value);
    free(new_env);
    new_env = ft_strdup(tmp);
    free(tmp);
    printf("new_env : %s\n", new_env);
    free(data->env[i]);
    data->env[i] = ft_strdup(new_env);
    free(new_env);

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
    data->env[i] = ft_strdup(new_env);
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
                temp = ft_strdup(arr[j]);
                free(arr[j]);
                arr[j] = ft_strdup(arr[j + 1]);
                free(arr[j + 1]);
                arr[j + 1] = ft_strdup(temp);
                free(temp);
            }
            j++;
    
        }
        i++;
    }
    return (arr);
}

char **cpy_envir(char **env)
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
    return (new_env);
}

int	ft_export(t_data *data, char **arg)
{
    int		i;
    char	*key;
    char	*value;
    int     env_len;
    char **new_env;
    char *arg_copy;

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
            value = ft_strdup(new_env[i]);
            key = ft_strtok(data, new_env[i], "=");
            free(new_env[i]);
            if (ft_strlen(value) - ft_strlen(key) == 0)
                printf("declare -x %s\n", key);
            else 
                printf("declare -x %s=\"%s\"\n", key, value + ft_strlen(key) + 1);
            free(key);
            free(value);
            i++;
        }
        free(new_env);
   
        return (0);
    }
    int s = 0;
    while (arg[s])
    {
        printf("\narg[%d] : %s\n", s, arg[s]);
     s++;
    }
    while (arg[i])
    {

        if (!ft_strchr(arg[i], '='))
        {
            printf("test\n");
            if (search_env(data, arg[i]) == -1 && arg[i])
            {
                if (!ft_isalpha(arg[i][0]) && arg[i][0] != '_')
                {
                    printf("minishell: export: `%s': not a valid identifier\n", arg[i]);
                    return 1;
                }
                add_env(data, arg[i], NULL); 
            }
            i++;
            continue;
        }
        if (ft_strnstr(arg[i], "+=", ft_strlen(arg[i])) != NULL)
        {
            key = ft_strtok(data, arg[i], "+=");
            if (key)
                value = ft_strdup(arg[i] + ft_strlen(key) + 2);
            if (search_env(data, key) == -1)  // Si la clé n'existe pas déjà
            {
                add_env(data, key, value);  // Ajouter la nouvelle variable
            }
            else
            {
                cat_env(data, key, value);  // Sinon, concaténer la valeur à la variable existante
            }
            free(key);
            free(value);
            i++;
            continue;
        }
        else
        {    
        arg_copy = ft_strdup(arg[i]);
        if (!ft_isalpha(arg[i][0]) && arg[i][0] != '_')
                {
                    printf("minishell: export: `%s': not a valid identifier\n", arg_copy);
                    free(arg_copy);
                    return 1;
                }

    key = ft_strtok(data, arg[i], "=");

            if (key)
            {
                if (ft_strlen(arg[i]) == ft_strlen(key) + 1)
                    value = ft_strdup("");
                else
                    value = ft_strdup(arg[i] + ft_strlen(key) + 1);
            }
            if (search_env(data, key) == -1)
            {
                
                add_env(data, key, value);
            }
            else
                {
                    printf("test2\n");
                    printf("key : %s\n", key);
                    printf("value : %s\n", value);
                change_env(data, key, value);
                }
            free(arg_copy);
            free(key);
            if (value)
                free(value);
            i++;
        }
    }
    return (0);
}