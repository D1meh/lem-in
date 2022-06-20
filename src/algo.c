#include "../includes/lem_in.h"

#define START 1
#define END 2

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
	printf("--- printQueue ---\n");
	while (i < len) {
		printf("[name = '%s' , visited =  %d]\n",  queue[i]->name, queue[i]->visited);
		i++;
	}
	printf("--- ---------- ---\n");
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

t_room **reverseQueue(t_room **queue) {
	// todo : reverse queue
	
	return queue;
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

	// If start is start then we found the path !
	if (path[0] == start)
		return path;
	
	// Else no path found
	return NULL;
}

t_room	**BFS(t_room	*start, t_room *end, t_data *anthill) {
	t_room	**queue = enqueue(NULL, start);
	t_room	**prev = initPrev(anthill->nbRooms);

	queue = enqueue(queue, start->next);
	start->visited = true;
	while (queueSize(queue) != 0) {
		// Select the next node of the queue 
		t_room *current = dequeue(&queue);
		// Store all neighbours of current in the queue
		for (size_t i = 0 ; i < current->nbOfLinks ; i++) {
			// Verify that the neighbours of current has not been visited yet
			if (!current->links[i]->visited) {
				// If not been visited, add to queue the node
				queue = enqueue(queue, current->links[i]);
				current->links[i]->visited = true;
				// Save the current as prev for each neighbours
				prev[current->links[i]->id] = current;
			}
		}
	}
	return (reconstructPath(start, end, prev));
}

void    algo(t_data *anthill) {
    // On trouve le nombre de chemin max
    // Si le nombre de fourmis est inferieur au nombre de chemins trouvé :
    // On reduit le nombre de chemin au nombre de fourmis
    // D'abord definir un max selon
    // le nombre de depart sur start et le nombre de depart sur end

    t_room *start = getSpecificRoom(anthill->rooms, START);
    t_room *end = getSpecificRoom(anthill->rooms, END);

	// Determines max paths possibilities
    int maxPossibilities = start->nbOfLinks >= end->nbOfLinks ? end->nbOfLinks : start->nbOfLinks;
	printf("maxPossibilities = %d\n", maxPossibilities);
	t_room **path = BFS(start, end, anthill);

	(void)path;
}