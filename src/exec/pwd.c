/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:19:50 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/04 11:39:16 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void pwd(void)
{
	int i;
	char *str;

	i = 1;
	str = ft_calloc(i, sizeof(char));
	while (getcwd(str, i) == NULL)
	{
		i++;
		free(str);
		str = ft_calloc(i, sizeof(char));
	}
	printf("%s", str);
}
