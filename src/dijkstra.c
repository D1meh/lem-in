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
	ft_putstr("-------- printQueue --------\n");
	while (i < len) {
		ft_putstr("[name = '"); ft_putstr(queue[i]->name); ft_putstr(", dist = ");
		ft_putnbr(queue[i]->currCost); ft_putstr("]\n");
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

t_room	**sortQueue(t_room **queue) {
	size_t	i = 0;
	size_t	j = 0;
	size_t	size = queueSize(queue);

	while (i < size) {
		int		min = 999999;
		size_t	minIdx = 0;

		// Find the node with the minimum cost
		j = i;
		while (queue[j]) {
			if (queue[j]->currCost < min) {
				min = queue[j]->currCost;
				minIdx = j;
			}
			j++;
		}
		// Then invert current index with the minimum index
		t_room	*temp = queue[i];
		queue[i] = queue[minIdx];
		queue[minIdx] = temp;
		i++;
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

t_room	**dijkstra(t_room *start, t_room *end, t_data *anthill) {
	t_room	**queue = enqueue(NULL, start);
	t_room	**prev = initPrev(anthill->nbRooms);

	start->visited = true;
	while (queueSize(queue) != 0) {

		// Sort the queue so that the closest node from start is picked to be examinated first
		queue = sortQueue(queue);
		// Pick the closest node with dequeue
		t_room *current = dequeue(&queue);

		// Check that we didn't examinated the node yet
		if (current->visited == true && current != start)
			continue ;

		// Mark node as visited so we do not return to it later (can cause infinite loop)
		current->visited = true;

		// Loop on all current's neighbours
		t_link	*currLinks = current->links;
		while (currLinks) {

			// Verify that the neighbours of the current node has not been visited yet
			if (!currLinks->node->visited) {

				// If not been visited, add to queue the node if and only if the distance is shorter
				// than it was to reach this node from start (dijsktra mandatory)
				if (currLinks->node->currCost == 0 || (current->currCost + currLinks->distance) < currLinks->node->currCost) {

					// Update the cost so we keep track of the distance made from start to this node
					currLinks->node->currCost = current->currCost + currLinks->distance;

					// Add then the node to the queue
					queue = enqueue(queue, currLinks->node);

					// Save the current as prev for each neighbours (Used to reconstruct the shortest path later)
					prev[currLinks->node->id] = current;
				}
			}
			currLinks = currLinks->next;
		}
	}
	free(queue);
	return (reconstructPath(start, end, prev));
}