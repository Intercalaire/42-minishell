/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:13:30 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/30 10:56:41 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	unset(t_data *data, int i, int j)
{
	int exit;
	int k;

	k = search_env(data->env, data->arg[i][j]);
	free(data->env[k]);
	while (data->env[k + 1])
	{
		data->env[k] = ft_strdup(data->env[k + 1]);
		if (!data->env[k])
			return (-1);
		free(data->env[k + 1]);
		k++;
	}
	if (data->arg[i][j + 1])
	{
		exit = unset(data, i, j + 1);
	}
	return (exit);
}
