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
		printf("[name = '%s' , visited = %d , score = %zu]\n",  queue[i]->name, queue[i]->visited, queue[i]->score);
		i++;
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

t_room	**enqueueNegativeCostFirst(t_room **queue, t_room *current, t_room ***prev) {
	for (size_t i = 0 ; current->links[i] ; i++) {
		if (current->distances[i] == -1) {
			printf("-1 found\n");
			queue = enqueue(queue, current->links[i]);
			current->links[i]->visited = true;
			(*prev)[current->links[i]->id] = current;
		}
	}
	return queue;
}

t_room	**BFS(t_room *start, t_room *end, t_data *anthill) {
	t_room	**queue = enqueue(NULL, start);
	t_room	**prev = initPrev(anthill->nbRooms);

	start->visited = true;
	while (queueSize(queue) != 0) {
		// Select the next node of the queue
		t_room *current = dequeue(&queue);

		// Store all neighbours of current in the queue
		// queue = enqueueNegativeCostFirst(queue, current, &prev);
		t_link	*currLinks = current->linkss;
		while (currLinks) {
			// Verify that the neighbours of current has not been visited yet
			if (!currLinks->node->visited) {
				// If not been visited, add to queue the node
				queue = enqueue(queue, currLinks->node);
				currLinks->node->visited = true;
				// Save the current as prev for each neighbours
				prev[currLinks->node->id] = current;
			}
			currLinks = currLinks->next;
		}
	}
	free(queue);
	return (reconstructPath(start, end, prev));
}