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
#include "../includes/lem_in.h"

void    *ft_malloc(size_t sizeOf, size_t size) {

    void    *ptr = malloc(sizeOf * size);
    if (!ptr)
   		ft_exit_error("Failed to allocate memory\n");
    return (ptr);
}