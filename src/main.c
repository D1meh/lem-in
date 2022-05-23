/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/23 18:15:34 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int    registerLine(t_data *anthill, char *line, unsigned int index) {
    printf("-> |%s|\n", line);
    if (index == 0)
    {
        int nbAnts = ft_atoi(line);
        if (nbAnts <= 0)
            return (-1);
        anthill->ants = malloc(sizeof(t_ant) * nbAnts);
        anthill->nbAnts = nbAnts;
    }
    else if (index > 0)
    {
        
    }
    return 1;
}

void    readInput(t_data *anthill, int fd) {
    char            *line = NULL;
    char            *prevLine;
    unsigned int    index = 0;
    while (1)
    {
        prevLine = line;
        if (get_next_line(fd, &line) < 1)
            break;
        registerLine(anthill, line, index);
        if (prevLine)
            free(line);
        index++;
    }
    registerLine(anthill, line, index);
    free(line);
}

int main() {

    t_data  anthill;

    readInput(&anthill, STDIN_FILENO);
    printf("Done\n");
    system("leaks lem-in");
}