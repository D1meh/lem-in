/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/07/04 16:35:29 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int main(int ac, char **av) {
	bool	debug = false;
    t_data  anthill;

	if (ac >= 2 && ft_strcmp("--debug", av[1]) == 0)
		debug = true;

	anthill.debug = debug;
    anthill.maxX = 0;
    anthill.maxY = 0;
	anthill.nbRooms = 0;

	// === Parsing and storing data === //
    char **lines = readInput();
    parseLines(lines, &anthill);

	if (anthill.debug)
    	printMap(&anthill);

	// === Print anthill === //
	for (size_t i = 0; lines[i] ; i++) {
		ft_putstr(lines[i]);
		ft_putstr("\n");
	}
	ft_putstr("\n");

	// === Solve paths and print results === //
    solve(&anthill);

	ft_putstr("\n");
}
