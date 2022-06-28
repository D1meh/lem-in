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
	t_room **newQueue = malloc(sizeof(t_room *) * (len + 2));
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
	t_room **newQueue = malloc(sizeof(t_room *) * (len));
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
		printf("{-- %s --|-- %s --}\n", (*paths)->path[0]->name, start->name);
		if ((*paths)->path[0] == start) {
			if (toDelete == NULL)
				toDelete = (*paths);
			times += 1;
		}
		(*paths) = (*paths)->next;
	}
	if (times >= 2 && toDelete) {
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

bool	BFS_FindPath(t_data *anthill, t_room *start, t_room* end, t_path **paths) {
	t_room	**path = NULL;

	path = BFS(start, end, anthill);
	if (path != NULL) {
		resetVisited(anthill->rooms);
		markPath(start, end, path);
		addPath(paths, initPath(path));
		deleteTwinPath(paths, start);
		resetVisited(anthill->rooms);
		return (true);
	}
	return (false);
}

void	usePrevPathAsRealPath(t_path **realPaths, t_path **paths, t_room *startingNode) {
	t_path	*tmp = NULL;
	t_path	*start = (*paths);
	while (*paths) {
		printf("*path->path[0]->name = %s | startingNode->name = %s\n", (*paths)->path[0]->name, startingNode->name);
		if ((*paths)->path[0] == startingNode)
			break ;
		(*paths) = (*paths)->next;
	}
	if (*paths) {
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

t_path	*solve(t_data *anthill) {

	t_path	*paths = NULL;
	t_path	*realPaths = NULL;

    t_room	*start = getSpecificRoom(anthill->rooms, START);
    t_room	*end = getSpecificRoom(anthill->rooms, END);

	start->used = true;

	size_t	maxPossibilities = start->nbOfLinks >= end->nbOfLinks ?
		end->nbOfLinks : start->nbOfLinks;

	printf("maxPossibilities = %zu\n", maxPossibilities);

	// Loop BFS to find all the shortest paths
	size_t	pathsFound = 0;

	// Essayer peut etre en black listant des nodes une à une trouvé sur le chemin le plus court
	printf("------ Trying ------\n");
	size_t	iterations = 0;
	size_t	i;
	bool	hasFound;
	while (iterations < 3) {
		i = 0;
		while (i < start->nbOfLinks && !start->links[i]->used) {
			printf("start->name = %s\n", start->links[i]->name);
			hasFound = BFS_FindPath(anthill, start->links[i], end, &paths);
			if (!hasFound && iterations >= 1) {
				usePrevPathAsRealPath(&realPaths, &paths, start->links[i]);
			}
			i += 1;
		}
		pathsFound = i;
		withoutMaxScore(anthill->rooms);

		printPaths(paths);
		iterations += 1;
	}
	printf("---------------------------------------\n");
	printPaths(realPaths);
	// paths = orderPath(paths);
	// printPaths(paths);
	// getOptimalPath(anthill, paths, pathsFound);
	// pathsFound = i - 1;
	// printPaths(paths);
	// system("leaks lem-in");
	return NULL;
}
