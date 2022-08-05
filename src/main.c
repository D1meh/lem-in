/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/08/05 19:20:52 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	printAnthill(char **lines) {

	for (size_t i = 0; lines[i] ; i++) {
		ft_putstr(lines[i]);
		ft_putstr("\n");
	}
	// ft_putstr("\n");
}

void	mainDebug(t_data anthill) {
	char	**lines;

	lines = readInput();
	parseLines(lines, &anthill);
	printMap(&anthill);
}

void	mainTime(t_data anthill) {
	char	**lines;

	printTime(lines = readInput());
    printTime(parseLines(lines, &anthill));
	printTime(solve(&anthill));
}

int main(int ac, char **av) {
	bool	debug = false;
	bool	time = false;
	t_data  anthill;

	anthill.maxX = 0;
	anthill.maxY = 0;
	anthill.nbRooms = 0;

	if (ac >= 2 && ft_strcmp("--debug", av[1]) == 0)
		debug = true;
	if (ac >= 2 && ft_strcmp("--time", av[1]) == 0)
		time = true;
	anthill.debug = debug;
	anthill.time = time;


	// === Parsing and storing data === //
	if (debug) {
		mainDebug(anthill);
	}
	else if (time) {
		mainTime(anthill);
	}
	else {
		char	**lines;

		lines = readInput();
		parseLines(lines, &anthill);
		printAnthill(lines);
		solve(&anthill);
	}
	ft_putstr("\n");

	// system("leaks lem-in");
	return (0);
}
