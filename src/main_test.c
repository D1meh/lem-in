#include "../includes/lem_in.h"
#include <math.h>


// t_queue	*createQueue(t_room *node) {
// 	t_queue	*new = malloc(sizeof(t_queue) * 1);

// 	new->node = node;
// 	new->next = NULL;
// 	new->prev = NULL;
	
// 	return new;
// }

// void	enqueue(t_queue **queue, t_room *node) {
// 	if (!node) return ;

// 	if (!(*queue))
// 		*queue = createQueue(node);
// 	else {
// 		// We sort the queue while adding so that we don't have to sort later
// 		t_queue *head = *queue;
// 		t_queue *new = createQueue(node);

// 		// Insert node at front
// 		if (node->currCost < (*queue)->node->currCost)
// 		{
// 			new->prev = NULL;
// 			new->next = *queue;
// 			(*queue)->prev = new;
// 			*queue = new;
// 			return ;
// 		}		
// 		while ((*queue)) {

// 			// Insert node in middle
// 			if ((*queue)->next && node->currCost < (*queue)->next->node->currCost)
// 			{
// 				new->prev = *queue;
// 				new->next = (*queue)->next;
// 				(*queue)->next->prev = new;
// 				(*queue)->next = new;
// 				*queue = head;
// 				return ;
// 			}
// 			// Insert node at the end
// 			else if (!((*queue)->next))
// 			{
// 				new->prev = *queue;
// 				new->next = NULL;
// 				(*queue)->next = new;
// 				*queue = head;
// 				return ;
// 			}
// 			*queue = (*queue)->next;
// 		}
// 	}	
// }

// typedef	struct s_queue {

// 	int	content;

// 	struct s_queue	*prev;
// 	struct s_queue	*next;
// }	t_queue;

// t_queue	*initQueue(int content) {
// 	t_queue	*new = malloc(sizeof(t_queue) * 1);

// 	new->content = content;
// 	new->next = NULL;
// 	new->prev = NULL;
	
// 	return new;
// }

// void	affQueue(t_queue *queue) {
// 	int size = 0;
// 	while (queue) {
// 		printf("[ %d ] ", queue->content);
// 		queue = queue->next;
// 		if (queue)
// 			printf("-> ");
// 		size++;
// 	}
// 	printf("\n size = %d\n", size);
// }

// void	revAffQueue(t_queue *queue) {
// 	int size = 0;
// 	while (queue->next)
// 		queue = queue->next;
// 	while (queue) {
// 		printf("[ %d ] ", queue->content);
// 		queue = queue->prev;
// 		if (queue)
// 			printf("-> ");
// 		size++;
// 	}
// 	printf("\n size = %d\n", size);
// }

// void	addQueue(t_queue **queue, int	content) {
// 	// if (!content) return ;

// 	if (!(*queue))
// 		*queue = initQueue(content);
// 	else {
// 		// We sort the queue while adding so that we don't have to sort later

// 		t_queue *head = *queue;
// 		t_queue *new = initQueue(content);

// 		// Insert node at front
// 		if (content < (*queue)->content)
// 		{
// 			new->prev = NULL;
// 			new->next = *queue;
// 			(*queue)->prev = new;
// 			*queue = new;
// 			return ;
// 		}		
// 		while ((*queue)) {

// 			// Insert node in middle
// 			if ((*queue)->next && content < (*queue)->next->content)
// 			{
// 				new->prev = *queue;
// 				new->next = (*queue)->next;
// 				(*queue)->next->prev = new;
// 				(*queue)->next = new;
// 				*queue = head;
// 				return ;
// 			}
// 			// Insert node at the end
// 			else if (!((*queue)->next))
// 			{
// 				new->prev = *queue;
// 				new->next = NULL;
// 				(*queue)->next = new;
// 				*queue = head;
// 				return ;
// 			}
// 			*queue = (*queue)->next;
// 		}
// 	}	
// }

// int	main(void) {
// 	srand(time(NULL));
// 	int i = 100;
// 	t_queue *queue = NULL;

// 	while (i--) {
// 		int	random = rand() % 10;
// 		addQueue(&queue, random);
// 	}
	
// 	affQueue(queue);
// 	printf("--------------------------------\n");
// 	revAffQueue(queue);
// 	return 0;
// }
