#include "../includes/lem_in.h"

void	printLinks(t_room *rooms) {
	ft_putstr("----- print links -----\n");
	while (rooms) {
		t_link	*links = rooms->links;
		ft_putstr("Links for [name="); ft_putstr(rooms->name); ft_putstr(", currCost=");
		ft_putnbr(rooms->currCost); ft_putstr("] visited= ["); ft_putnbr(rooms->visited); ft_putstr("] \t-> [");
		while (links) {
			ft_putstr(links->node->name); ft_putstr("(");
			ft_putnbr(links->distance); ft_putstr("), ");
			links = links->next;
		}
		ft_putstr("\b\b]\n");
		rooms = rooms->next;
	}
	ft_putstr("----- print links end -----\n");
}

void	deleteLink(t_link **links, t_link *toDelete) {

	t_link	*start = *links;
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
			// Find and Delete the link with the previous node in the path
			t_link	*prevLinks = previous->links;
			while (prevLinks) {
				if (prevLinks->node == current) {
					deleteLink(&previous->links, prevLinks);
					// printf("invertVertex: %s - %s\n", previous->name, prevLinks->node->name);
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

void	resetLinks(t_room *start) {
	while (start) {
		while (start->links) {
			t_link	*tmpLink = start->links;
			start->links = start->links->next;
			free(tmpLink);
		}
		start->links = start->saveLinks;
		start = start->next;
	}
}

void	removeAllInverseEdges(t_path *paths) {
	
	t_path	*start = paths;
	t_path	*save;
	t_room	**currPath;
	t_room	*first = NULL;
	t_room	*second = NULL;
	// Loop on every path
	while (paths) {

		currPath = paths->path;
		// Loop on every node in the path
		for (size_t i = 0; currPath[i + 1]; i++)
		{
			// Save the start node in memory
			save = start;

			// Invert two nodes in the current path
			second = currPath[i];
			first = currPath[i + 1];

			// Then we gonna try to find the same couple in an another path
			// If we find so, we delete those links for the futur
			if (first && second) {

				// Loop on every path
				while (start) {
					if (start != paths) {

						// Loop on every node in the path
						for (size_t i = 0; start->path[i]; i++)
						{	
							if (first == start->path[i] && second == start->path[i + 1]) {
								deleteLink(&(first->links), findLinkByName(first->links, second->name));
								deleteLink(&(second->links), findLinkByName(second->links, first->name));
							}
								
						}
					}
					start = start->next;
				}
				
			}
			start = save;
		}
		
		paths = paths->next;
	}
	paths = start;
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

void	Bhandari_Algorithm(t_data *anthill, t_room *start, t_room* end, t_path **paths, size_t *nbOfPath) {
	bool	hasFound = true;

	while (hasFound) {

		/* ========== STEP 1 ========== */
		// Find the shortest path with Dijkstra's algorithm
		hasFound = FindShortestPath(anthill, start, end, paths);
		if (hasFound) {
			*nbOfPath += 1;

			/* ========== STEP 2 ========== */
			// Replace the edges from the found path
			// with inverse edges with negative costs.
			// and reset data in all nodes between each iteration
			invertVertexes(lastPath(*paths));
			// printLinks(anthill->rooms);
		}
	
		resetCost(anthill->rooms);

		/* ========== STEP 3 ========== */
		// Repeat step 1 and 2 for n shortest paths
	}
}

t_path	*solve(t_data *anthill) {

	t_path	*paths = NULL;

	t_room	*start = getSpecificRoom(anthill->rooms, START);
	t_room	*end = getSpecificRoom(anthill->rooms, END);

	size_t	nbOfPath = 0;
	
	start->visited = true;

	// Bhandari Algorithm all steps followed :
	// Step 1, 2 and 3 are here
	Bhandari_Algorithm(anthill, start, end, &paths, &nbOfPath);
	if (!paths)
		exitError("No solution found for this map.\n");

	/* ========== STEP 4 ========== */
	// Add all shortest paths in the graph. (Done by calling FindShortestPath())
	if (nbOfPath >= 2) {
		resetLinks(anthill->rooms);
		// Step 5 :
		// Remove all inverse edges along with their originals,
		// so they cancel each other out.
		removeAllInverseEdges(paths);

		// Then repeat algo to find all the disjoint paths since we deleted the links
		nbOfPath = 0;
		freePaths(paths);
		paths = NULL;
		Bhandari_Algorithm(anthill, start, end, &paths, &nbOfPath);
	}
	letsFuckingGo(anthill, paths, nbOfPath);
	freePaths(paths);
	return NULL;
}
