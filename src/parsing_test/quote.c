/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:39:17 by vgodart           #+#    #+#             */
/*   Updated: 2024/05/03 17:39:19 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec_test/minishell.h"

static int	quote(t_data *data, char *str, int in_qte_dble, int in_qte_sple);
static char *ft_utils_trim_quote(char *str, int j, char *ret, char quote);

int	quote_verif(t_data *data, char *str)
{
	int	i;
	int	in_quote_simple;
	int	in_quote_double;

	i = 0;
	in_quote_simple = 0;
	in_quote_double = 0;
	while (str[i])
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
	if (quote(data, str, in_quote_double, in_quote_simple) == 1)
		return (1);
	return (0);
}

static int	quote(t_data *data, char *str, int in_qte_dble, int in_qte_sple)
{
	if (in_qte_dble == 1)
	{
		ft_little_error_prog(data, str, QUOTE_DBL);
		return (1);
	}
	if (in_qte_sple == 1)
	{
		ft_little_error_prog(data, str, QUOTE_SMP);
		return (1);
	}
	return (0);
}

char	*ft_trim_quote(t_data *data, char *str)
{
    int	i;
    int	j;
    int	len;
    char	*ret;
    char	quote;

    i = 0;
    j = 0;
    quote = 0;
    len = ft_strlen(str);
	if (!str)
		return (NULL);
    ret = malloc(sizeof(char) * (len + 1));
    if (!ret)
        ft_error_prog(data, str, "Error");
    while (str[i] && !quote)
    {
        if (str[i] == '"' || str[i] == '\'')
            quote = str[i];
        i++;
    }
	return (ft_utils_trim_quote(str, j, ret, quote));
}

static char *ft_utils_trim_quote(char *str, int j, char *ret, char quote)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != quote)
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}