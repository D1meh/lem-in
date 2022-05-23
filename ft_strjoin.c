/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:43:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/23 11:07:27 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char    *ft_strjoin(char *s1, char *s2)
{
    if (!s1 || !s2)
        return NULL;
    char *dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    int i = -1;
    int j = 0;
    while (s1[++i])
        dest[i] = s1[i];
    while (s2[j])
        dest[i++] = s2[j++];
    dest[i] = 0;
    return dest;
}

int main(void)
{
    char *a = "Hey";
    char *b = "Hay";

    char *c = ft_strjoin(a, b);
    printf("%s %i\n", c, ft_strlen(c));
}