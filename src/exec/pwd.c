/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:19:50 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/15 12:28:21 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*
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
*/
int pwd(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PWD=", 4) && !strncmp(env[i], "OLDPWD=", 7))
		{	
			printf("%s", substr(env[i], 4, strlen(env[i])));
			return(0);
		}
		i++;
	}
	return(2);
}

char **env(char **environnement)
{
	char **env;
	int len_env;
	int i;

	len_env = 0;
	while (environnement[len_env])
		len_env++;
	env = calloc(len_env, sizeof(*char));
	if (!env)
		exit("Alloc Error\n");
	while (environnement[i])
	{
		env[i] = strdup(environnement[len_env])
		i++;
	}
	return(env);
}
int main(int argc, char **argv, char **env)
{
	void(argc);
	void(argv);
	pwd(env(env));

}
