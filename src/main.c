/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/23 21:37:18 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void    free_tab(char **tab) {
    int i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}

void    ft_exit_error(char *error) {
    write(STDERR, RED, ft_strlen(RED));
    write(STDERR, "Error: ", 7);
    write(STDERR, error, ft_strlen(error));
    write(STDERR, RESET, ft_strlen(RESET));
    exit(EXIT_FAILURE);
}

void    storeNbAnts(char *line, t_data *anthill) {
    if (!line)
        ft_exit_error("Invalid format for 'number of ants'.\n");
    if (!ft_strisdigit(line))
        ft_exit_error("Invalid format for 'number of ants'.\n");
    int nbAnts = ft_atoi(line);
    if (nbAnts <= 0)
        ft_exit_error("Invalid number of ants.\n");
    anthill->ants = ft_malloc(sizeof(t_ant), nbAnts);
    anthill->nbAnts = nbAnts;
    printf("Ants -> %s\n", line);
}

int storeRoom(char *line, int type) {
    char    **tab = ft_split(line, ' ');
    int     len = 0;
    while (tab[++len]);
    if (len != 3)
        ft_exit_error("Invalid format for 'the_rooms'.\n");
    
    printf("Room -> %s %s\n", line,  type == 1 ? "(Start)" : type == 2 ? "(End)" : "");
    free_tab(tab);
    return 1;
}

void storeLinks(char *line) {
    char    **tab = ft_split(line, '-');
    int     len = 0;
    while (tab[++len]);
    if (len != 2)
        ft_exit_error("Invalid format for 'the_links'.\n");
    
    printf("Link -> %s\n", line);
    free_tab(tab);
}

void    parseLines(char **lines, t_data *anthill) {
    int     part = 0; // number_of_ants - the_rooms - the_links
    int     type = 0;
    for (size_t i = 0 ; lines[i] != NULL ; i++) {

        /* Skip comments */
        if (lines[i][0] == '#' && ft_strcmp(lines[i], "##start") && ft_strcmp(lines[i], "##end"))
            continue ;

        type = 0;
        if (ft_strcmp(lines[i], "##start") == 0)
            type = 1;
        else if (ft_strcmp(lines[i], "##end") == 0)
            type = 2;

        /* Store number_of_ants */
        if (part == 0) {
            storeNbAnts(lines[i], anthill);
            part++;
        }
        /* Store the_rooms */
        else if (part == 1) {
            /* Go to part 3 if there is a '-' */
            if (ft_strchr(lines[i], '-')) {
                i--;
                part++;
                continue ;
            }
            if (type != 0)
                i++;
            storeRoom(lines[i], type);
        }
        /* Store the_links */
        else if (part == 2) {
            storeLinks(lines[i]);
        }
    }
}

char    **readInput() {
	char	**tab = NULL;
	char	*line = NULL;

	while (get_next_line(STDIN, &line) > 0) {
		tab = ft_pushback(tab, line);
    }
	tab = ft_pushback(tab, line);
    return (tab);
}

int main() {

    t_data  anthill;

    char **lines = readInput();
    parseLines(lines, &anthill);
    printf("Done\n");
    system("leaks lem-in");
}