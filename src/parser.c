#include "../includes/lem_in.h"

typedef	struct s_lines {

	char	*line;
	struct s_lines	*next;

}	t_lines;

size_t	sizeLines(t_lines *lines) {
	size_t i = 0;
	while (lines) { lines = lines->next; i++; }
	return (i);
}

char	**tabify(t_lines *lines) {
	size_t	size = sizeLines(lines);
	char	**tab = ft_malloc(sizeof(char *), size + 1);
	t_lines *temp = NULL;
	tab[size] = NULL;
	
	for (int i = size ; i--;) {

		tab[i] = lines->line;
		temp = lines;

		lines = lines->next;
		free(temp);
	}

	return (tab);
}

void	addLine(t_lines **lines, char *newLine) {

	t_lines *new = ft_malloc(sizeof(t_lines), 1);

	new->line = newLine;
	new->next = *lines;

	*lines = new;
}

void	freeTab(char **tab) {
	int i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	storeNbAnts(char *line, t_data *anthill) {
	if (!line)
		exitError("Invalid format for 'number_of_ants'.\n");
	if (!ft_strisdigit(line))
		exitError("Invalid format for 'number of ants'.\n");
	long int nbAnts = ft_atoi(line);
	if (nbAnts <= 0 || nbAnts >= INT_MAX)
		exitError("Invalid number of ants.\n");
	anthill->nbAnts = nbAnts;
}

bool storeRoom(char *line, int type, t_data *anthill) {
	if (!line) {
		exitError("Invalid format for 'the_rooms'.\n");
	}

	char	**tab = ft_split(line, ' ');
	int	 len = 0;
	while (tab[++len]);
	if (len != 3 || !ft_strisdigit(tab[1]) || !ft_strisdigit(tab[2])) {
		freeTab(tab);
		return false;
	}
	unsigned int x = ft_atoi(tab[1]);
	unsigned int y = ft_atoi(tab[2]);
	t_room	*new = createRoom(ft_strdup(tab[0]), x, y, type);
	if (!avoidDoubeRoom(anthill->rooms, new)) {
		freeTab(tab);
		free(new->name);
		free(new);
		return true;
	}
	anthill->nbRooms += 1;
	addRoom(&(anthill->rooms), new);

	x > anthill->maxX ? anthill->maxX = x : 0;
	y > anthill->maxY ? anthill->maxY = y : 0;

	freeTab(tab);
	return true;
}

bool	storeLinks(char *line, t_data *anthill) {
		
	char	**tab = ft_split(line, '-');
	int	 len = 0;
	while (tab[++len]);
	if (len != 2)
		return false;

	t_room *r1 = findRoomByName(tab[0], anthill->rooms);
	t_room *r2 = findRoomByName(tab[1], anthill->rooms);
	if (!r1 || !r2) {
		freeTab(tab);
		return true;
	}

	if (avoidDoubleLink(r1, tab[1]))
		addLinkForRoom(r1, anthill->rooms, tab[1]);
	if (avoidDoubleLink(r2, tab[0]))
		addLinkForRoom(r2, anthill->rooms, tab[0]);

	freeTab(tab);
	return true;
}

void	parseLines(char **lines, t_data *anthill) {
	int	 part = 0; // number_of_ants - the_rooms - the_links
	int	 type = 0;
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

	if (!validStartEnd(anthill->rooms))
		exitError("Invalid end or start for 'the_rooms'.\n");
}

char	**readInput() {
	t_lines	*lines = NULL;
	char	*line = NULL;

	while (get_next_line(STDIN, &line) > -1) {
		if (!line || !line[0] || line[0] == '\n')
			break ;
		addLine(&lines, line);
	}
	free(line);
	return (tabify(lines));
}

void printMap(t_data *anthill) {
	unsigned int	x = 0;
	unsigned int	y = 0;
	t_room		  *r = NULL;
	browseRooms(anthill->rooms);
	while (y <= anthill->maxY) {

		while (x <= anthill->maxX) {

			r = findRoomByPos(anthill->rooms, x, y);
			if (r) {
				ft_putstr_fd(STDERR, "\t");
				ft_putstr_fd(STDERR, r->name);
			}
			else
				ft_putstr_fd(STDERR, "\t---");
			x++;
		}
		ft_putstr_fd(STDERR, "\n");
		x = 0;
		y++;
	}
}