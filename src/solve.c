#include "../includes/lem_in.h"

void	printLinks(t_room *rooms) {
	while (rooms) {
		t_link	*links = rooms->links;
		printf("Links for [name=%s, currCost=%d] -> [", rooms->name, rooms->currCost);
		while (links) {
			printf("%s(%d), ", links->node->name, links->distance);
			links = links->next;
		}
		printf("\b\b]\n");
		rooms = rooms->next;
	}
}

// t_room	*getNearest(t_link *links) {
// 	int		minDist = 999;
// 	t_room	*nearestNode = NULL;
// 	while (links) {
// 		if (!links->node->visited && links->distance < minDist) {
// 			minDist = links->distance;
// 			nearestNode = links->node;
// 		}
// 		links = links->next;
// 	}
// 	return (nearestNode);
// }

// void	dijkstra(t_data *anthill, t_room *start, t_room *end) {
// 	t_room	*nodes = start;
// 	(void)end;
// 	(void)anthill;
// 	while (nodes) {
// 		t_room	*nearest = getNearest(nodes->links);
// 		if (nearest) {
// 			printf("nearest from [%s] is [%s]\n", nodes->name, nearest->name);
// 			nearest->visited = true;
// 		}
// 		nodes = nodes->next;
// 	}
// }

bool	FindShortestPath(t_data *anthill, t_room *start, t_room* end, t_path **paths) {
	t_room	**path = NULL;

	printLinks(anthill->rooms);
	path = BFS(start, end, anthill);
	if (path != NULL) {
		addPath(paths, initPath(path));
		printf("here\n");
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
		printPaths(paths);
		printLinks(start);
		iterations += 1;
	}
	// system("leaks lem-in");
	return NULL;
}
