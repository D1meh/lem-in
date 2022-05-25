/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:05:00 by epfennig          #+#    #+#             */
/*   Updated: 2022/05/25 17:23:08 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void    free_tab(char **tab) {
    int i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}

void    storeNbAnts(char *line, t_data *anthill) {
    if (!line)
        exitError("Invalid format for 'number_of_ants'.\n");
    if (!ft_strisdigit(line))
        exitError("Invalid format for 'number of ants'.\n");
    long int nbAnts = ft_atoi(line);
    if (nbAnts <= 0 || nbAnts > 99999)
        exitError("Invalid number of ants.\n");
    anthill->ants = ft_malloc(sizeof(t_ant), nbAnts);
    anthill->nbAnts = nbAnts;
    printf("Ants -> %ld\n", nbAnts);
}

bool storeRoom(char *line, int type, t_data *anthill) {
    if (!line) {
        printf("Debug 1\n");
        exitError("Invalid format for 'the_rooms'.\n");
    }

    char    **tab = ft_split(line, ' ');
    int     len = 0;
    while (tab[++len]);
    if (len != 3 || !ft_strisdigit(tab[1]) || !ft_strisdigit(tab[2])) {
        free_tab(tab);
    	return false;
    }
    
	t_room	*new = createRoom(ft_strdup(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]), type);
    if (!avoidDoubeRoom(anthill->rooms, new)) {
        free_tab(tab);
        free(new->name);
        free(new);
        return true;
    }
	addRoom(&(anthill->rooms), new);
    printf("Room -> %s %s\n", line,  type == 1 ? "(Start)" : type == 2 ? "(End)" : "");
    free_tab(tab);
    return true;
}

bool    storeLinks(char *line, t_data *anthill) {
    
    char    **tab = ft_split(line, '-');
    int     len = 0;
    while (tab[++len]);
    if (len != 2)
		return false;
    
    t_room *r1 = findRoomByName(tab[0], anthill->rooms);
    t_room *r2 = findRoomByName(tab[1], anthill->rooms);
    if (!r1 || !r2) {
        free_tab(tab);
        return true;
    }
    
    if (avoidDoubleLink(r1, tab[1]))
       r1->links = ft_pushback(r1->links, tab[1]);
    if (avoidDoubleLink(r2, tab[0]))
        r2->links = ft_pushback(r2->links, tab[0]);

    // printf("Link -> %s\n", line);
    free_tab(tab);
	return true;
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
            if (!storeLinks(lines[i], anthill))
				break ;
        }
    }
	browseRooms(anthill->rooms);
	if (!validStartEnd(anthill->rooms))
		exitError("Invalid end or start for 'the_rooms'.\n");
}

char    **readInput() {
	char	**tab = NULL;
	char	*line = NULL;

	while (get_next_line(STDIN, &line) > 0) {
        if (!line || !line[0])
            break ;
		tab = ft_pushback(tab, line);
        free(line);
    }
	tab = ft_pushback(tab, line);
    free(line);
    return (tab);
}

int main() {

    t_data  anthill;

    char **lines = readInput();
    parseLines(lines, &anthill);
    printf("Done\n");
    // system("leaks lem-in");
}
