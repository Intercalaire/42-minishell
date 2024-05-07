/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:18:09 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/04 11:13:23 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//dans les cas ou c'est different de echo, cd, pwd, export, unset, env, exit
void path(void)
{
	char *path;
	char **var;
	int bin;

	path = ft-calloc(strlen(getenv("PATH")), sizeof(char *));
	path = getenv("PATH");
	printf("%s", path);
	var = ft_split(path, ":");
	while (var[i])
	{
		if (ft_strncmp(var[i], "/bin", 5) == 0)
			break ;
		i++;
	}
	if (!var[i])
		error("No /bin/");
	else
		bin = i;
	execve(cmd, arg, var[bin]);
	//argv = commande + arguments

}

int main(void)
{
	path();
	return 0;
}