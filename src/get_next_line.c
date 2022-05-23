/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:08:23 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/23 18:22:19 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				get_next_line(int fd, char **line)
{
	ssize_t		ret;                                                          /* return de read    ssize_t = pour aller dans les negatifs (-1 / 0 / 1) */
	char		buff[BUFFER_SIZE + (ret = 1)];                                /* buffer / ligne qu'on lis on va stocker dedans ce qu'on lis puis on rentrera buf dans str qui est static */
	static char	*str = NULL;                                                  /* destination de ce que l'on va lire. (static * = stock l'adresse memoire) pour garder en memoir ou on en est */
	char		*temp;

	if (fd < 0 || fd >= 256 || !line || BUFFER_SIZE <= 0)                     /* gestion d'erreur */
		return (-1);
	str == NULL ? str = ft_memalloc(1 * sizeof(char)) : NULL;                 /* verification de la static pour savoir si c'est le premier appel de gnl ou non, on alloue 1 bit pour le '\0' */
	while (!ft_strchr(str, '\n') && (ret = read(fd, buff, BUFFER_SIZE)) > 0)  /* Tant que l'on a pas de '\n' et que le read() lis (ret = le return de read, le nombre de bit lus) */
	{
		buff[ret] = '\0';                                                     /* on met le '\0' a la fin de la string buff (notre ligne lue en fonction du buffer_size) pour permettre le ft_strjoin */
		temp = ft_strjoin(str, buff);                                         /* strjoin de la static str avec la ligne lue, qu'on stock dans temp le temps de free l'ancienne adresse de str */
		ft_strfree(&str);                                                     /* on free l'adresse de str pour ensuite lui reassigner temp pour ne pas avoir de leaks et de superposition de string */
		str = temp;                                                           /* assignation de str avec le nouvel strjoin */
	}                                                                         /* on check le ret a la sortie de la boucle, on sort si ret <= 0 ou si l'on a trouvé le '\n' */
	if (ret == 0)                                                             /* si ret = 0 , cela veut dire que il n'y a plus rien a lire car ret = 0*/
		*line = ft_strdup(str);                                               /* on copy + malloc dans *line qui est notre ligne finale de retour, on fait strdup car on a l'EOF donc on a la len qu'il nous faut*/
	else if (ret > 0)                                                         /* si ret > 0 cela veut dire qu'on n'est pas arrivé a l'EOF donc on fait un substr*/
		*line = ft_substr(str, 0, (ft_strchr(str, '\n') - str));              /* strchr - str c'est adresse d'un pointeur - l'adresse de l'autre et ca fait un int : on part de start = 0 et len = la position du '\n' */
	else                                                                      /* on calcule avec strchr - str = l'adresse du \n dans str */
		return (-1);                                                          /* else on trouve une erreur dans le ret (ret < 0) */
	temp = ft_strdup(str + (ft_strlen(*line) + ((ret > 0) ? +1 : +0)));       /* partie on l'on stoque le reste pour la suite du programme */
	ft_strfree(&str);                                                         /* on free une derniere fois l'adresse de str */
	str = temp;
	return (ret == 0 ? 0 * ft_strfree(&str) : 1);                             /* valeur de return, on reverifie le ret de read, si on est a l'EOF, on free &str tout en renvoyant 0 */
}                                                                             /* sinon on return 1 == une ligne a été lu */
