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
	for (size_t i = 0; lines[i] ; i++)
		printf("%s\n", lines[i]);

	// === Solve paths and print results === //	
    solve(&anthill);

	//system("leaks lem-in");
}
