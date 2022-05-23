/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/23 17:21:38 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int    registerLine(t_data *anthill, char *line) {
    (void)anthill;
    printf("-> |%s|\n", line);
    return 1;
}

void	printError() {
	write(2, "ERROR", 5);
	exit(1);
}

void    readInput(t_data *anthill, int fd) {

    char    *line;
	char	**splitLine;
	int		count = 0;

    while (get_next_line(fd, &line) < 1 && ft_strlen(line) && !ft_isspace(line)) {

		if (line[0] == 'L') {
			free(line);
			printError();
		}

		

		free(line);
	}
}

int main(void) {
    
    t_data  anthill;

    readInput(&anthill, STDIN_FILENO);
    system("leaks lem-in");
    printf("Done\n");
}