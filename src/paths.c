#include "../includes/lem_in.h"

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
		for (size_t i = 0; i < nbOfPath; i++) {
			if (i == nbOfPath-1 || cost[i] <= cost[i+1]) {
				comb[i]++;
				cost[i]++;
				ants--;
				break ;
			}
		}
	}
	printer(anthill, pathList, comb);
}
