#include "../includes/lem_in.h"

#define ADD 0
#define RET 1

void printFinalTab(int **tab, int sizeOfTab, int nbAnts) {

	for (int i = 0; i < sizeOfTab; i++) {
		for (int j = 0; j < nbAnts; j++) {
			printf("%d ", tab[i][j]);
		}
		printf("\n");
	}
}

int	**getFinalTab(int arr[], int param, int size) {
	static int **tab = NULL;
	static int len = 0;
	int **newTab;
	int *toAdd;

	if (param == ADD) {
		toAdd = calloc(sizeof(int), size);
		for (int i = 0; i < size; i++) {
			toAdd[i] = arr[i];
		}
		newTab = malloc(sizeof(int*) * (len+1));
		for (int i = 0; i < len; i++) {
			newTab[i] = tab[i];
		}
		newTab[len] = toAdd;
		len++;
		free(tab);
		tab = newTab;
	}

	if (param == RET)
		return tab;
	return NULL;
}

void findComb(int arr[], int index, int n, int reducedN, int *size) {
	if (reducedN < 0)
		return ;

	if (reducedN == 0) {
		getFinalTab(arr, ADD, n);
		*size = *size + 1;
		return ;
	}

	int prev = (index == 0) ? 1 : arr[index-1];
	for (int i = prev; i < n; i++) {
		arr[index] = i;
		findComb(arr, index+1, n, reducedN-i, size);
	}
}

void initFindComb(int n, int *size) {
	int arr[n];
	findComb(arr, 0, n, n, size);
}

void getOptimalPath(t_data *anthill, t_room ***pathList, int nbOfPath) {
	int sizeOfTab = 0, ants = anthill->nbAnts;
	int osef[1];	// variable inutile juste pour avoir un param dans getFinalTab
	(void)pathList;

	initFindComb(ants, &sizeOfTab);
	int **tab = getFinalTab(osef, RET, 0);
	printFinalTab(tab, sizeOfTab, ants);

	int *nbMoves = malloc(sizeof(int) * sizeOfTab);
	for (int i = 0; i < sizeOfTab; i++) {
		int sum = 0;

	}
}