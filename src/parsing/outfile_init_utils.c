/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_init_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 04:43:40 by vgodart           #+#    #+#             */
/*   Updated: 2024/08/03 04:43:42 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

char	*ft_strdup_outfile(t_data *data, const char *s, int y, int hdoc)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	str = NULL;
	str = ft_calloc((i + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i-- != 0)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	if (hdoc == 1 && (ft_strchr(str, '\'') || ft_strchr(str, '"')))
		data->output->h_doc_count[y] = 1;
	else if (hdoc == 1)
		data->output->h_doc_count[y] = 0;
	return (ft_trim_quote(str));
}
