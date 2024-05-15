/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsolet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:10:52 by hsolet            #+#    #+#             */
/*   Updated: 2024/05/15 10:42:53 by hsolet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int pipe()
{
	int i;
	int *son_pid;

	i = 0;
	while (i < nbr_pipe)
	{
		son_pid[i] = fork();
		if (son_pid[i] == -1)
			erreur();
		i++;
	}
	i = 0;
	while (son_pid[i] != getpid())
		i++;
	/*
	 - ecrire chaque resultat dans un fichier que je vide apres lecture et que je reecris en boucle et detruit a la fin
	 - ecrire dans une chaine de charactere les resultats et envoyer dans le fd demander que au niveau du pere
	 - faire la premiere action et ajouter le resultat en argument de la prochaine action 
	 
	 */
	///////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////
	if (son_pid[i] == 0)
		return(/*jsp encore mais c'est la fin*/);
}
