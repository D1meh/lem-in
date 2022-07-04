#include "../includes/lem_in.h"

int minCost(int cost[], size_t nbOfPath) {
	int min = 0;
	int minVal = cost[0];
	for (size_t i = 1; i < nbOfPath; i++) {
		if (minVal > cost[i]) {
			min = i;
			minVal = cost[i];
		}
	}
	return min;
}

void letsFuckingGo(t_data *anthill, t_path *pathList, size_t nbOfPath) {
	int *comb = ft_malloc(sizeof(int), nbOfPath);
	int cost[nbOfPath];
	int ants = anthill->nbAnts;
	t_path *current = pathList;

	for (size_t i = 0; i < nbOfPath; i++) {
		cost[i] = pathLen(current->path);
		comb[i] = 0;
		current = current->next;
	}

	while (ants) {
		int min = minCost(cost, nbOfPath);
		comb[min]++;
		cost[min]++;
		ants--;
	}
	printer(anthill, pathList, comb);
	free(comb);
}
