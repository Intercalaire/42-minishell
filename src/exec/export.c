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


int export(t_data *data)
{
    int i;
    int len_var;

    i = 0;
    search_env(data->env, data->command->arg);
    len_var = ft_strnstr(data->command->cmd, , 6);
}
static char add_env(char **env, char *key, char *value)
{
    int		i;
    char	*new_env;

    i = 0;
    while (env[i])
        i++;
    new_env = ft_calloc((ft_strlen(key) + ft_strlen(value) + 2), sizeof(char);
    if (!new_env)
        return (NULL);
    ft_strcpy(new_env, key);
    ft_strcat(new_env, "=");
    ft_strcat(new_env, value);
    env[i] = new_env;
    env[i + 1] = NULL;
    return (env);
}

static char change_env(char **env, char *key, char *value)
{
    int		i;
    char	*new_env;

    i = search_env(env, key);
    new_env = ft_calloc((ft_strlen(key) + ft_strlen(value) + 2), sizeof(char);
    if (!new_env)
        return (NULL);
    ft_strcpy(new_env, key);
    ft_strcat(new_env, "=");
    ft_strcat(new_env, value);
    free(env[i]);
    env[i] = new_env;
    return (env);
}

int	export(t_data *data, char **args)
{
    int		i;
    char	*key;
    char	*value;

    i = 1;
    while (args[i])
    {
        key = ft_strtok(args[i], "=");
        if (key)
            value = ft_strdup(args[i] + ft_strlen(key) + 1);
        if (!key || !value)
            return (ft_putstr_fd("Usage: export NAME=VALUE\n", 1));
        if (search_env(data->env, key) == -1)
            data->env = add_env(data->env, key, value);
        else
            data->env = change_env(data->env, key, value);
        i++;
    }
    return (0);
}