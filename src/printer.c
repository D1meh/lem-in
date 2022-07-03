#include "../includes/lem_in.h"

int	getNumberOfPath(int *comb, int ants) {
	int i = 0, sum = 0;
	while (sum < ants) {
		sum += comb[i];
		i++;
	}
	return i;
}

int	endNode(t_path *pathList) {
	size_t len = queueSize(pathList->path);
	return len-1;
}

void printer(t_data *anthill, t_path *pathList, int *comb) {
	int pathsToUse = getNumberOfPath(comb, anthill->nbAnts);
	int hasReached = 0;
	int waitingAnts = anthill->nbAnts;

	while (hasReached < anthill->nbAnts) {
		t_path *currPath = pathList;
		int left = pathsToUse;

		while (left) {
			int currRoom = endNode(currPath);

			while (currRoom > 0 && currPath->path[currRoom]->hasAnAnt == false)
				currRoom--;

			while (currRoom > -1) {

				if (currRoom != 0 && currPath->path[currRoom]->hasAnAnt == true) {
					printf("L%d-%s ", currPath->path[currRoom]->idAnt, currPath->path[currRoom+1]->name);

					if (currPath->path[currRoom+1]->type != END) {
						currPath->path[currRoom+1]->hasAnAnt = true;
						currPath->path[currRoom+1]->idAnt = currPath->path[currRoom]->idAnt;
					} else {
						hasReached++;
					}

					currPath->path[currRoom]->hasAnAnt = false;
					currPath->path[currRoom]->idAnt = 0;

				} else if (currRoom == 0 && waitingAnts && comb[left-1]) {
					waitingAnts--;
					comb[left-1]--;
					currPath->path[currRoom+1]->hasAnAnt = true;
					currPath->path[currRoom+1]->idAnt = anthill->nbAnts - waitingAnts;
					printf("L%d-%s ", currPath->path[currRoom+1]->idAnt, currPath->path[currRoom+1]->name);
				}

				currRoom--;
			}

			left--;
			currPath = currPath->next;
		} // end paths

	printf("\n");
	}	// end ants have reached
}