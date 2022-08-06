#include "../includes/lem_in.h"
#include "../includes/visualizer.h"

size_t	movesLen(char **moves) {
	size_t i = 0;

	while (moves && moves[i])
		i++;
	return (i);
}

void	printSteps(solveStep *steps) {
	size_t	idx = 0;
	while (steps) {
		printf("--- Idx = %zu ---\n", idx);
		for (int i = 0; i < steps->antsByStep ; i++)
			printf("%s -> %s\n", steps->ants[i].id, steps->ants[i].roomName);
		steps = steps->next;
		idx++;
	}
}

solveStep	*getLastStep(solveStep *steps) {
	while (steps && steps->next)
		steps = steps->next;
	return steps;
}

solveStep	*createStep(char **moves, t_data *anthill, solveStep *prevStep) {
	(void)prevStep;
	char		**antRoom = NULL;
	solveStep	*new = ft_malloc(sizeof(solveStep), 1);
	t_room		*start = getSpecificRoom(anthill->rooms, START);

	new->next = NULL;
	new->prev = NULL;
	new->ants = NULL;
	new->antsByStep = movesLen(moves);

	if (moves) {
		new->ants = ft_malloc(sizeof(Ant), movesLen(moves));
		for (int i = 0 ; moves[i] ; i++) {
			antRoom = ft_split(moves[i], '-');

			t_room	*room = findRoomByName(antRoom[1], anthill->rooms);
			new->ants[i].id = antRoom[0];
			new->ants[i].roomName = antRoom[1];

			new->ants[i].wantedX = room->x;
			new->ants[i].wantedY = room->y;

			new->ants[i].currX = start->x;
			new->ants[i].currY = start->y;

			free(antRoom);
		}
	}
	return (new);
}

void	addStep(solveStep **steps, char **moves, t_data *anthill) {
	solveStep	*new = createStep(moves, anthill, getLastStep(*steps));
	if (!(*steps)) {
		(*steps) = createStep(NULL, anthill, NULL);
		(*steps)->next = new;
		new->prev = (*steps);
	}
	else {
		solveStep	*last = getLastStep(*steps);

		last->next = new;
		new->prev = last;
	}
}

bool	parseSolution(char **solution, solveStep **steps, t_data *anthill) {
	char	**moves = NULL;
	if (!solution)
		return false;
	for (int i = 0 ; solution[i] ; i++) {
		moves = ft_split(solution[i], ' ');
		addStep(steps, moves, anthill);
		if (moves) {
			for (int i = 0 ; moves[i] ; i++)
				free(moves[i]);
			free(moves);
		}
		free(solution[i]);
	}
	free(solution);
	return true;
}
