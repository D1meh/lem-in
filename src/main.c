/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/26 15:42:01 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int main() {

    t_data  anthill;

    anthill.maxX = 0;
    anthill.maxY = 0;
	anthill.nbRooms = 0;
    char **lines = readInput();
    parseLines(lines, &anthill);
    printMap(&anthill);
    algo(&anthill);
    printf("Done\n");
}
