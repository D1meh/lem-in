#include "../includes/lem_in.h"

size_t	queueSize(t_room **queue) {
	size_t i = 0;
	if (!queue) return 0;
	while (queue[i]) i++;
	return i;
}

void	printQueue(t_room **queue) {
	size_t	i = 0;
	size_t	len = queueSize(queue);
	while (i < len) {
		printf("[name = '%s' , visited = %d , used = %d , score = %zu]\n",  queue[i]->name, queue[i]->visited, queue[i]->used, queue[i]->score);
		i++;
	}
}

void	withoutMaxScore(t_room *rooms) {
	t_room	*maxScore = rooms;
	while (rooms) {
		if (maxScore->score <= rooms->score)
			maxScore = rooms;
		rooms = rooms->next;
	}
	printf("Blacklisting [%s]\n", maxScore->name);
	maxScore->used = true;
}

t_room **reverseQueue(t_room **queue) {
	size_t	i = 0;
	size_t	j = queueSize(queue) - 1;
	t_room	*temp = NULL;

	while (i < j) {
		temp = queue[i];
		queue[i] = queue[j];
		queue[j] = temp;
		i++;
		j--;
	}
	return queue;
}

t_room **enqueue(t_room **queue, t_room *node) {
	if (!node) return queue;
	
	size_t len = queueSize(queue);
	t_room **newQueue = ft_malloc(sizeof(t_room *), (len + 2));
	size_t i = 0;

	while (i < len) {
		newQueue[i] = queue[i];
		i++;
	}
	if (queue)
		free(queue);
	newQueue[i] = node;
	newQueue[i + 1] = NULL;
	return newQueue;
}

t_room *dequeue(t_room ***queue) {
	if (!*queue || !*queue[0]) return NULL;
	
	size_t len = queueSize(*queue);
	t_room **newQueue = ft_malloc(sizeof(t_room *), (len));
	size_t i = 0;

	while (i < len - 1) {
		newQueue[i] = (*queue)[i + 1];
		i++;
	}
	t_room *ret = *queue[0];
	free(*queue);
	newQueue[i] = NULL;
	*queue = newQueue;
	return ret;
}

t_room	**reconstructPath(t_room *start, t_room *end, t_room **prev) {
	t_room	**path = NULL;

	// Reconstruct the path using the prev for each node : end -> ... -> start
	for (t_room	*at = end ; at != NULL ; at = prev[at->id]) {
		path = enqueue(path, at);
	}
	// Then reverse the path to have start -> ... -> end
	path = reverseQueue(path);
	free(prev);

	// If start is start then we found the path !
	if (path[0] == start)
		return path;

	// Else no path found
	free(path);
	return NULL;
}

t_room	**BFS(t_room *start, t_room *end, t_data *anthill) {
	t_room	**queue = enqueue(NULL, start);
	t_room	**prev = initPrev(anthill->nbRooms);

	start->visited = true;
	while (queueSize(queue) != 0) {
		// Select the next node of the queue
		t_room *current = dequeue(&queue);
		// Store all neighbours of current in the queue
		for (size_t i = 0 ; i < current->nbOfLinks ; i++) {
			// Verify that the neighbours of current has not been visited yet
			if (!current->links[i]->visited && !current->links[i]->used) {
				// If not been visited, add to queue the node
				queue = enqueue(queue, current->links[i]);
				current->links[i]->visited = true;
				// Save the current as prev for each neighbours
				prev[current->links[i]->id] = current;
			}
		}
	}
	free(queue);
	return (reconstructPath(start, end, prev));
}

void	deleteTwinPath(t_path **paths, t_room *start) {
	t_path	*save = *paths;
	t_path	*toDelete = NULL;
	size_t	times = 0;
	while (*paths) {
		if ((*paths)->path[0] == start) {
			if (toDelete == NULL)
				toDelete = (*paths);
			times += 1;
		}
		(*paths) = (*paths)->next;
	}
	if (times >= 2 && toDelete) {
		printf("deleteTwinPath [%s]\n", toDelete->path[0]->name);
		if (toDelete->prev) {
			toDelete->prev->next = toDelete->next;
			toDelete->next->prev = toDelete->prev;
			free(toDelete);
			*paths = save;
		}
		else {
			t_path	*tmp = toDelete->next;
			free(toDelete);
			toDelete = tmp;
			toDelete->prev = NULL;
			*paths = tmp;
		}
	}
	else
		*paths = save;
}

bool	FindShortestPath(t_data *anthill, t_room *start, t_room* end, t_path **paths) {
	t_room	**path = NULL;

	path = BFS(start, end, anthill);
	if (path != NULL) {
		resetVisited(anthill->rooms);
		// markPath(start, end, path);
		addPath(paths, initPath(path));
		// deleteTwinPath(paths, start);
		return (true); 
	}
	return (false);
}

void	usePrevPathAsRealPath(t_path **realPaths, t_path **paths, t_room *startingNode) {
	t_path	*tmp = NULL;
	t_path	*start = (*paths);
	while (*paths) {
		if ((*paths)->path[0] == startingNode)
			break ;
		(*paths) = (*paths)->next;
	}
	if (*paths) {
		printf("usePrevPathAsRealPath [%s]\n", (*paths)->path[0]->name);
		addPath(realPaths, initPath((*paths)->path));
		if ((*paths)->prev) {
			(*paths)->prev->next = (*paths)->next;
			(*paths)->next->prev = (*paths)->prev;
			free((*paths));
			(*paths) = start;
		}
		else {
			tmp = (*paths)->next;
			free((*paths));
			(*paths) = tmp;
			(*paths)->prev = NULL;
		}
	}
	else
		*paths = start;
}

void	deleteLink(t_room **tab, size_t idx, size_t *nbOfLinks) {

	for (size_t i = 0; i < *nbOfLinks; i++) {
		if (i >= idx) {
			if (i == *nbOfLinks - 1)
				tab[i] = NULL;
			else
				tab[i] = tab[i + 1];
		}
	}
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
			printf("---\ncurrent : [%s]\n", current->name);
			printf("previous : [%s]\n", previous->name);
			size_t	j = 0;
			while (j < previous->nbOfLinks) {
				if (previous->links[j] == current) {
					printf("previous->links[j] = [%s]\n---\n", previous->links[j]->name);
					deleteLink(previous->links, j, &previous->nbOfLinks);
				}
				j++;
			}
		}
		i++;
	}
	return ;
}

t_path	*solve(t_data *anthill) {

	t_path	*paths = NULL;

    t_room	*start = getSpecificRoom(anthill->rooms, START);
    t_room	*end = getSpecificRoom(anthill->rooms, END);

	start->used = true;

	size_t	maxPossibilities = start->nbOfLinks >= end->nbOfLinks ?
		end->nbOfLinks : start->nbOfLinks;

	printf("maxPossibilities = %zu\n", maxPossibilities);

	// Essayer peut etre en black listant des nodes une à une trouvé sur le chemin le plus court
	printf("------ Trying ------\n");
	size_t	iterations = 0;
	bool	hasFound;
	browseRooms(anthill->rooms);
	while (iterations < 2) {
		hasFound = FindShortestPath(anthill, start, end, &paths);
		printPaths(paths);
		invertVertexes(lastPath(paths));
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
