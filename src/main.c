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

void    readInput(t_data *anthill, int fd) {

    // char    *buff = malloc(sizeof(char) * 0);
    char    *line;
    // char    *tmp = NULL;

    // size_t  r = 0;
    while (42)
    {    
        if (get_next_line(fd, &line) < 1) {
            registerLine(anthill, line);
            break ;
        }
        registerLine(anthill, line);
    }
}

int main(int ac, char **av) {
    (void)ac;
    (void)av;
    
    t_data  anthill;

    readInput(&anthill, STDIN_FILENO);
    system("leaks lem-in");
    printf("Done\n");
}