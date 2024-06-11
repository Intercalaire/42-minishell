/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:26:27 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/03 14:26:30 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_trim_quote(char *str);

char	*ft_strdup(const char *s)
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
	str = ft_calloc((i + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i != 0)
	{
		str[j] = s[j];
		i--;
		j++;
	}
	return (str);
}

char	*ft_strdup_2(const char *s)
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
	while (i != 0)
	{
		str[j] = s[j];
		i--;
		j++;
	}
	result = ft_trim_quote(str);
	free(str);
	return (result);
}

static char	*ft_trim_quote(char *str)
{
    int i = 0;
    int j = 0;
    char quote = 0;
    int len = ft_strlen(str);
    char *result = malloc(sizeof(char) * (len + 1));

    while (str[i]) {
        if ((str[i] == '"' || str[i] == '\'') && quote == 0) {
            quote = str[i];
        } else if (str[i] == quote) {
            quote = 0;
        } else if (quote == '"' && (str[i] == '$' || str[i] == '`' || str[i] == '\\' || str[i] == '!')) {
            result[j++] = '\\';
            result[j++] = str[i];
        } else {
            result[j++] = str[i];
        }
        i++;
    }
    result[j] = '\0';
    return result;
}
