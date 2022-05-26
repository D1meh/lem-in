/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:43:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/26 10:12:57 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int			i;
	int			j;
	char		*str;

	if (s1 == NULL || s2 == NULL || !(str = (char *)ft_malloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	str[0] = '\0';
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
