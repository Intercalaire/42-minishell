/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredocs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 05:10:53 by hsolet            #+#    #+#             */
/*   Updated: 2024/08/08 05:10:55 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/parsing/minishell.h"

static void	handle_special_case_two(t_data *data, char **temp, char **ptr)
{
	char	*value;

	value = ft_itoa(data->exit_status);
	ft_strncpy(*temp, value, ft_strlen(value));
	*temp += ft_strlen(value);
	free(value);
	*ptr += 2;
}

static void	copy_normal_chars(char **temp, char **ptr)
{
	**temp = **ptr;
	(*temp)++;
	(*ptr)++;
}

static void	build_final_string(t_data *data, char *result, char *line, int i)
{
	char	*temp;
	char	*ptr;

	temp = result;
	ptr = line;
	while (*ptr)
	{
		if (*ptr == '$' && data->output->h_doc_count[i] == 0)
		{
			if (*(ptr + 1) == '?')
				handle_special_case_two(data, &temp, &ptr);
			else
				handle_env_var_two(data, &temp, &ptr);
		}
		else
			copy_normal_chars(&temp, &ptr);
	}
	*temp = '\0';
}

char	*expand_env_vars(t_data *data, char *line, int i)
{
	int		size_needed;
	char	*result;

	size_needed = calculate_size_needed(data, line);
	result = malloc(size_needed);
	if (!result)
		return (NULL);
	build_final_string(data, result, line, i);
	return (result);
}

int	create_tmp_file(char *tmpfiles)
{
	int	fd;

	fd = open(tmpfiles, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error("Minishell: ", tmpfiles, ": No such file or directory");
		free(tmpfiles);
	}
	return (fd);
}
