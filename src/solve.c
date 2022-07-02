#include "../includes/lem_in.h"

void	printLinks(t_room *rooms) {
	printf("----- print links -----\n");
	while (rooms) {
		t_link	*links = rooms->links;
		printf("Links for [name=%s, currCost=%d] \t-> [", rooms->name, rooms->currCost);
		while (links) {
			printf("%s(%d), ", links->node->name, links->distance);
			links = links->next;
		}
		printf("\b\b]\n");
		rooms = rooms->next;
	}
	printf("----- print links end -----\n");
}

void	deleteLink(t_link **links, t_link *toDelete, size_t *nbOfLinks) {

	t_link	*start = *links;

	if (*nbOfLinks == 0)
		return ;
	while (*links) {
		if (*links == toDelete)
			break ;
		*links = (*links)->next;
	}
	if (*links) {
		if ((*links)->prev) {
			(*links)->prev->next = (*links)->next;
			if ((*links)->next)
				(*links)->next->prev = (*links)->prev;
			free((*links));
			*links = start;
		}
		else {
			t_link	*tmp = (*links)->next;
			free((*links));
			(*links) = tmp;
			if (*links)
				(*links)->prev = NULL;
			*links = tmp;
		}
	}
	else
		*links = start;
	*nbOfLinks -= 1;
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
			printf("current = [%s] && previous = [%s]\n", current->name, previous->name);
			// Find and Delete the link with the previous node in the path
			t_link	*prevLinks = previous->links;
			while (prevLinks) {
				if (prevLinks->node == current) {
					printf("prevLinks->node = [%s]\n", prevLinks->node->name);
					deleteLink(&previous->links, prevLinks, &previous->nbOfLinks);
					break ;
				}
				prevLinks = prevLinks->next;
			}

			t_link	*currLinks = current->links;
			while (currLinks) {
				if (currLinks->node == previous) {
					currLinks->distance = -1;
				}
				currLinks = currLinks->next;
			}
		}
		i++;
	}
	return ;
}

bool	FindShortestPath(t_data *anthill, t_room *start, t_room* end, t_path **paths) {
	t_room	**path = NULL;

	path = dijkstra(start, end, anthill);
	if (path != NULL) {
		addPath(paths, initPath(path));
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

	size_t	iterations = 0;
	bool	hasFound;

	while (iterations < 3) {
		hasFound = FindShortestPath(anthill, start, end, &paths);
		invertVertexes(lastPath(paths));
		printPaths(paths);
		printLinks(start);
		resetCost(start);
		iterations += 1;
	}
	printPaths(paths);

	// system("leaks lem-in");
	return NULL;
}
