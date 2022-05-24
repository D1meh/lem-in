/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/23 22:06:39 by epfennig         ###   ########.fr       */
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
    write(STDERR, "ERROR\n", 6);
    write(STDERR, error, ft_strlen(error));
    write(STDERR, RESET, ft_strlen(RESET));
    exit(EXIT_FAILURE);
}

void    storeNbAnts(char *line, t_data *anthill) {
    if (!line)
        ft_exit_error("Invalid format for 'number of ants'.\n");
    if (!ft_strisdigit(line))
        ft_exit_error("Invalid format for 'number of ants'.\n");
    long int nbAnts = ft_atoi(line);
    if (nbAnts <= 0)
        ft_exit_error("Invalid number of ants.\n");
    anthill->ants = ft_malloc(sizeof(t_ant), nbAnts);
    anthill->nbAnts = nbAnts;
    printf("Ants -> %ld\n", nbAnts);
}

int storeRoom(char *line, int type, t_data *anthill) {
    if (!line)
        ft_exit_error("Invalid format for 'the_rooms'.\n");

    char    **tab = ft_split(line, ' ');
    int     len = 0;
    while (tab[++len]);
    if (len != 3 || !ft_strisdigit(tab[1]) || !ft_strisdigit(tab[2]))
        //ft_exit_error("Invalid format for 'the_rooms'.\n");
		return 0;
    
	t_room	*new = createRoom(ft_strdup(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]), type);
	addRoom(&(anthill->rooms), new);
    printf("Room -> %s %s\n", line,  type == 1 ? "(Start)" : type == 2 ? "(End)" : "");
    free_tab(tab);
    return 1;
}

int storeLinks(char *line) {
    if (!line)
        ft_exit_error("Invalid format for 'the_links'.\n");
    
    char    **tab = ft_split(line, '-');
    int     len = 0;
    while (tab[++len]);
    if (len != 2)
        //ft_exit_error("Invalid format for 'the_links'.\n");
		return 0;
    
    printf("Link -> %s\n", line);
    free_tab(tab);
	return 1;
}

void    parseLines(char **lines, t_data *anthill) {
    int     part = 0; // number_of_ants - the_rooms - the_links
    int     type = 0;
	anthill->rooms = NULL;

    for (size_t i = 0 ; lines[i] != NULL ; i++) {
        if (!lines[i] || !lines[i][0])
            break ;
        /* Skip comments */
        if (lines[i][0] == '#' && ft_strcmp(lines[i], "##start") && ft_strcmp(lines[i], "##end"))
            continue ;

        /* Check if line is start or end node */
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
            if (!storeRoom(lines[i], type, anthill))
				break ;
        }
        /* Store the_links */
        else if (part == 2) {
            if (!storeLinks(lines[i]))
				break ;
        }
    }
	browseRooms(anthill->rooms);
	if (!validStartEnd(anthill->rooms))
		ft_exit_error("Invalid format for 'the_rooms'.\n");
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
    //system("leaks lem-in");
}