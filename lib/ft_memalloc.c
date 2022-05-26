/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:11:37 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/26 10:11:09 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lib.h"

char			*ft_memalloc(size_t size)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!(str = ft_malloc(1, size)))
		return (NULL);
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}