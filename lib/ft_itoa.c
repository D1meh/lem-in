/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:14:57 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/26 10:10:30 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

long int	ft_noneg(long int nb)
{
	if (nb < 0)
	{
		return (-nb);
	}
	return (nb);
}

int			ft_intlen(long int nb)
{
	int		len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * (-1);
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	len = ft_intlen(n);
	sign = (n < 0) ? -1 : 1;
	if ((str = (char *)ft_malloc(sizeof(char), (len + 1))) == NULL)
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = '0' + ft_noneg(n % 10);
		n = ft_noneg(n / 10);
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}