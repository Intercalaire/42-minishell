/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable_more_more_utils.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 04:35:29 by vgodart           #+#    #+#             */
/*   Updated: 2024/07/18 04:35:31 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing/minishell.h"

char	*ft_itoa_free(int n, char *to_free)
{
	char	*str;

	str = ft_itoa(n);
	free(to_free);
	return (str);
}

char	*ft_strdup_free(const char *s, char *to_free)
{
	char	*str;

	str = ft_strdup(s);
	free(to_free);
	return (str);
}
