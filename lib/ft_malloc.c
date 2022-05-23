/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:27:55 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/23 18:44:59 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

void    *ft_malloc(size_t sizeOf, size_t size) {

    void    *ptr = malloc(sizeOf * size);
    if (!ptr)
    {
        write(2, "Error: Failed to allocate memory\n", 33);
        exit(EXIT_FAILURE);
    }
    return (ptr);
}