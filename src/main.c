/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/23 19:07:20 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int    registerLine(t_data *anthill, char *line, unsigned int index) {
    printf("-> |%s|\n", line);
    if (line[0] == '#' && ft_strcmp(line, "##start") && ft_strcmp(line, "##end"))
        return 0;
    if (index == 0)
    {
        int nbAnts = ft_atoi(line);
        if (nbAnts <= 0)
            return (-1);
        anthill->ants = ft_malloc(sizeof(t_ant), nbAnts);
        anthill->nbAnts = nbAnts;
        printf("nbAnts : %d\n", anthill->nbAnts);
    }
    else if (index > 0)
    {
        
    }
    return 1;
}

void	printError() {
	write(2, "ERROR", 5);
	exit(1);
}

void    parseLines(char ** lines) {

    for (size_t i = 0 ; lines[i] != NULL ; i++) {
        if (lines[i][0] == '#' && ft_strcmp(lines[i], "##start") && ft_strcmp(lines[i], "##end"))
            continue ;
        printf("%s\n", lines[i]);
    }
}

void    readInput(t_data *anthill, int fd) {
    char            *line = NULL;
    while (1)
    {
        if (get_next_line(fd, &line) < 1)
            break;
        registerLine(anthill, line, index);
        if (prevLine)
            free(prevLine);
        index++;
    }
    if (prevLine)
        free(prevLine);
    registerLine(anthill, line, index);
    free(line);
}

int main() {

    t_data  anthill;

    readInput(&anthill, STDIN_FILENO);
    printf("Done\n");
    system("leaks lem-in");
}