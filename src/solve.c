#include "../includes/lem_in.h"

void	printLinks(t_room *rooms) {
	while (rooms) {
		t_link	*links = rooms->linkss;
		printf("Links for [%s] -> [", rooms->name);
		while (links) {
			printf("%s, ", links->node->name);
			links = links->next;
		}
		printf("\b\b]\n");
		rooms = rooms->next;
	}
}

bool	FindShortestPath(t_data *anthill, t_room *start, t_room* end, t_path **paths) {
	t_room	**path = NULL;
	(void)start;
	(void)end;
	(void)paths;
	printLinks(anthill->rooms);
	if (path != NULL) {
		// resetVisited(anthill->rooms);
		// markPath(start, end, path);
		// addPath(paths, initPath(path));
		// deleteTwinPath(paths, start);
		return (true); 
	}
	return (false);
}

t_path	*solve(t_data *anthill) {

	t_path	*paths = NULL;

    t_room	*start = getSpecificRoom(anthill->rooms, START);
    t_room	*end = getSpecificRoom(anthill->rooms, END);

	start->visited = true;

	size_t	maxPossibilities = start->nbOfLinks >= end->nbOfLinks ?
		end->nbOfLinks : start->nbOfLinks;

	printf("maxPossibilities = %zu\n", maxPossibilities);

	// Essayer peut etre en black listant des nodes une à une trouvé sur le chemin le plus court
	printf("------ Trying ------\n");
	size_t	iterations = 0;
	bool	hasFound;
	browseRooms(anthill->rooms);
	while (iterations < 1) {
		hasFound = FindShortestPath(anthill, start, end, &paths);
		iterations += 1;
	}
	browseRooms(anthill->rooms);
	printf("\n------------------ Finished ---------------------\n\n");
	// paths = orderPath(paths);
	// printPaths(paths);
	// getOptimalPath(anthill, paths, pathsFound);
	// pathsFound = i - 1;
	// printPaths(paths);
	// system("leaks lem-in");
	return NULL;
}
