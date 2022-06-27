#include "../includes/lem_in.h"

#define START 1
#define END 2

int	pathLen(t_room **path) {
	return (*path == 0 ? 0 : pathLen(path+1) + 1);
}

int nbOfPath(t_room ***pathList) {
	return (**pathList == 0 ? 0 : nbOfPath(pathList+1) + 1);
}

t_room ***orderPath(t_room ***pathList) {
	for (int i = 1; pathList[i]; i++) {
		t_room **a = pathList[i];
		int b = i;
		while (b > 0 && pathLen(pathList[b-1]) > pathLen(a)) {
			pathList[b] = pathList[b-1];
			b--;
		}
		pathList[b] = a;
	}
	return pathList;
}

t_room ***addToList(t_room ***pathList, t_room **path, int found) {

	t_room ***newList = malloc(sizeof(t_room **) * (found + 2));
	
	int i = 0;
	while (i < found) {
		newList[i] = pathList[i];
		i++;
	}
	newList[i] = path;
	newList[i + 1] = NULL;
	free(pathList);
	return newList;
}

t_room **initPrev(size_t size) {
	t_room	**prev = malloc(sizeof(t_room *) * (size + 1));

	size_t	i = 0;
	while (i < size) {
		prev[i] = NULL;
		i++;
	}
	prev[size] = NULL;
	return prev;
}

size_t	queueSize(t_room **queue) {
	size_t i = 0;
	if (!queue) return 0;
	while (queue[i]) i++;
	return i;
}

void	printQueue(t_room **queue) {
	size_t	i = 0;
	size_t	len = queueSize(queue);
	printf("-----printQueue-----\n");
	while (i < len) {
		printf("[name = '%s' , visited = %d , used = %d]\n",  queue[i]->name, queue[i]->visited, queue[i]->used);
		i++;
	}
	printf("--------------------\n");
}

void printList(t_room ***pathList) {
	if (!pathList) return;
	for (int i = 0; pathList[i] != NULL; i++) {
		printf("PATH NUMBER %d\n", i);
		printQueue(pathList[i]);
	}
}

void	markPathUsed(t_room *start, t_room *end, t_room **path) {
	size_t	i = 0;
	size_t	len = queueSize(path);
	while (i < len) {
		if (start != path[i] && end != path[i])
			path[i]->used = true;
		i++;
	}
}

void	resetVisited(t_room *rooms) {
	while (rooms) {
		rooms->visited = false;
		rooms = rooms->next;
	}
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

size_t	BFS_Loop(t_data *anthill, t_room *start, t_room* end, t_room ****pathList) {
	t_room	**path = NULL;

	size_t pathFound = 0;

	while ((path = BFS(start, end, anthill)) != NULL) {
		resetVisited(anthill->rooms);
		markPathUsed(start, end, path);
		*pathList = addToList(*pathList, path, pathFound);
		pathFound += 1;
	}
	resetVisited(anthill->rooms);
	return (pathFound);
}

void    solve(t_data *anthill) {

	t_room	***pathList = NULL;
	// t_room	**blackList = initPrev(anthill->nbRooms);
	// (void)blackList;
    t_room	*start = getSpecificRoom(anthill->rooms, START);
    t_room	*end = getSpecificRoom(anthill->rooms, END);

	size_t	maxPossibilities = start->nbOfLinks >= end->nbOfLinks ?
		end->nbOfLinks : start->nbOfLinks;

	printf("maxPossibilities = %zu\n", maxPossibilities);

	// Loop BFS to find all the shortest paths
	size_t	pathFound = BFS_Loop(anthill, start, end, &pathList);

	if (pathFound == 0) 
		exitError("Solver: Their is no solution path for this map.\n");

	pathList = orderPath(pathList);
	printList(pathList);
	getOptimalPath(anthill, pathList, nbOfPath(pathList));

	// Essayer peut etre en black listant des nodes une à une trouvé sur le chemin le plus court
	if (pathFound != maxPossibilities) {
		// printf("------ Trying ------\n");
		// size_t i = 0;
		// while (i < start->nbOfLinks && !start->links[i]->used) {
		// 	pathList = NULL;
		// 	printf("start->name = %s\n", start->links[i]->name);
		// 	// browseRooms(anthill->rooms);
		// 	pathFound = BFS_Loop(anthill, start->links[i], end, &pathList);
		// 	printList(pathList);
		// 	i++;
		// }
	}
}
