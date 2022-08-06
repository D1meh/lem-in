/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:33:03 by epfennig          #+#    #+#             */
/*   Updated: 2022/08/07 01:36:36 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

typedef	struct s_queue {

	t_room	*node;

	struct s_queue	*prev;
	struct s_queue	*next;
}	t_queue;

void	freeQueue(t_queue *queue) {
	t_queue	*temp;
	while (queue) {
		temp = queue;
		queue = queue->next;
		free(temp);
	}
}

size_t	queueSize(t_queue *queue) {
	size_t i = 0;
	if (!queue) return 0;
	while (queue) {
		i++;
		queue = queue->next;
	}
	return i;
}

t_queue	*createQueue(t_room *node) {
	t_queue	*new = ft_malloc(sizeof(t_queue), 1);

	new->node = node;
	new->next = NULL;
	new->prev = NULL;

	return new;
}

t_room **reverseQueue(t_queue *queue) {

	size_t	j = queueSize(queue);
	t_room	**reversed = ft_malloc(sizeof(t_room), j + 1);
	reversed[j] = NULL;

	while (queue->next) queue = queue->next;

	for (int i = 0 ; queue ; i++) {
		reversed[i] = queue->node;
		queue = queue->prev;
	}
	return reversed;
}

// enqueue add a node in order
// so that we don't have to sort later
void	enqueue(t_queue **queue, t_room *node, bool wantSort) {
	if (!node) return ;

	// printf("enqueue: %s\n", node->name);
	if (!(*queue)) {
		*queue = createQueue(node);
		return ;
	}

	t_queue *head = *queue;
	t_queue *new = createQueue(node);

	if (wantSort == false)
	{
		// Simple add back
		while ((*queue)->next) *queue = (*queue)->next;
		new->prev = (*queue);
		new->next = NULL;
		(*queue)->next = new;
		*queue = head;
		return ;
	}

	// Insert node in front
	if (node->currCost < (*queue)->node->currCost)
	{
		new->prev = NULL;
		new->next = *queue;
		(*queue)->prev = new;
		*queue = new;
		return ;
	}		
	while ((*queue)) {
		// Insert node in middle
		if ((*queue)->next && node->currCost < (*queue)->next->node->currCost)
		{
			new->prev = *queue;
			new->next = (*queue)->next;
			(*queue)->next->prev = new;
			(*queue)->next = new;
			*queue = head;
			return ;
		}
		// Insert node in end
		else if (!((*queue)->next))
		{
			new->prev = *queue;
			new->next = NULL;
			(*queue)->next = new;
			*queue = head;
			return ;
		}
		*queue = (*queue)->next;
	}
}

t_room *dequeue(t_queue **queue) {
	if (!*queue) return NULL;
	t_queue *first = (*queue);
	t_room	*ret = first->node;

	(*queue) = (*queue)->next;
	if (*queue) (*queue)->prev = NULL;
	free(first);

	return ret;
}

t_room	**reconstructPath(t_room *start, t_room *end, t_room **prev) {
	t_queue	*queuePath = NULL;

	// Reconstruct the path using the prev for each node : end -> ... -> start
	for (t_room	*at = end ; at != NULL ; at = prev[at->id]) {
		enqueue(&queuePath, at, false);
	}
	// Then reverse the path to have start -> ... -> end
	t_room **path = reverseQueue(queuePath);

	free(prev);
	freeQueue(queuePath);

	// If start is start then we found the path !
	if (path[0] == start)
		return path;

	// Else no path found
	free(path);
	return NULL;
}

t_room	**dijkstra(t_room *start, t_room *end, t_data *anthill) {

	t_queue	*queue = NULL;
	t_room	**prev = initPrev(anthill->nbRooms);

	enqueue(&queue, start, true);

	start->visited = true;
	while (queueSize(queue) != 0) {

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
					enqueue(&queue, currLinks->node, true);

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