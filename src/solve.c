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

void	deleteLink(t_link **links, t_link *toDelete, size_t *nbOfLinks) {
	(void)links;
	(void)toDelete;
	(void)nbOfLinks;
	// for (size_t i = 0; i < *nbOfLinks; i++) {
	// 	if (i >= idx) {
	// 		if (i == *nbOfLinks - 1)
	// 			tab[i] = NULL;
	// 		else
	// 			tab[i] = tab[i + 1];
	// 	}
	// }
	// *nbOfLinks -= 1;
}

void	invertVertexes(t_path *lastPath) {
	if (!lastPath)
		return ;

	size_t	i = 1;
	t_room	*previous = NULL;
	t_room	*current = NULL;
	while (lastPath->path[i]) {
		current = lastPath->path[i];
		previous = lastPath->path[i - 1];
		if (current && previous) {

			printf("---\ncurrent : [%s]\n", current->name);
			printf("previous : [%s]\n", previous->name);
			
			// Find and Delete the link with the previous node in the path
			t_link	*prevLinks = previous->links;
			while (prevLinks) {
				if (prevLinks->node == current) {
					printf("prevLinks->node[j] = [%s]\n", prevLinks->node->name);
					deleteLink(&previous->links, prevLinks, &previous->nbOfLinks);
				}
				prevLinks = prevLinks->next;
			}

			t_link	*currLinks = current->links;
			while (currLinks) {
				if (currLinks->node == previous) {
					printf("current->links[j] = [%s]\n", currLinks->node->name);
					currLinks->distance = -1;
				}
				printf("current->distances[j] = [%d]\n", currLinks->distance);
				currLinks = currLinks->next;
			}
			printf("---\n");
		}
		i++;
	}
	return ;
}

bool	FindShortestPath(t_data *anthill, t_room *start, t_room* end, t_path **paths) {
	t_room	**path = NULL;

	printLinks(anthill->rooms);
	path = dijkstra(start, end, anthill);
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
		invertVertexes(lastPath(paths));
		iterations += 1;
	}
	// system("leaks lem-in");
	return NULL;
}
