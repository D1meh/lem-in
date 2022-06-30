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

void	dijkstra(t_anthill *anthill, t_room *start, t_room *end) {
	t_room	*iter = start;
	while (iter) {
		iter = iter->next;
	}
}

bool	FindShortestPath(t_data *anthill, t_room *start, t_room* end, t_path **paths) {
	t_room	**path = NULL;
	(void)start;
	(void)end;
	(void)paths;
	printLinks(anthill->rooms);

	dijkstra(anthill, start, end);
	if (path != NULL) {
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

	browseRooms(anthill->rooms);

	size_t	iterations = 0;
	bool	hasFound;
		
	while (iterations < 1) {
		hasFound = FindShortestPath(anthill, start, end, &paths);
		iterations += 1;
	}

	// paths = orderPath(paths);
	// printPaths(paths);
	// getOptimalPath(anthill, paths, pathsFound);
	// pathsFound = i - 1;
	// printPaths(paths);
	// system("leaks lem-in");
	return NULL;
}
