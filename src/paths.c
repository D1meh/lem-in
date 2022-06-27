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
		toAdd = malloc(sizeof(int) * size);
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
	for (int i = prev; i <= n; i++) {
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

	initFindComb(ants, &sizeOfTab);
	int **tab = getFinalTab(osef, RET, 0);
	printFinalTab(tab, sizeOfTab, ants);

	int **nbMoves = malloc(sizeof(int*) * sizeOfTab);
	int filledMoves = 0;
	for (int i = 0; i < sizeOfTab; i++) {

		int sum = 0, j = 0, path = 0;

		// Checking that the combination is valid (example : for 4 ants, 1 1 1 1 on 3 paths isn't valid, 1 1 2 is)
		while (j < nbOfPath && sum < ants) {
			sum += tab[i][j];
			j++;
		}
		if (sum < ants)
			continue ;
		
		// Calculating how many moves it will take given the length of the paths and the numbers of ants sent in a path
		// using the following formula : max(M1, M2, ...Mn) with Mk = length path + nb of ants - 1
		int max = 0;
		for (int k = j-1; k >= 0; k--) {
			int len = pathLen(pathList[path]) + tab[i][k] - 2; // minus 2 because pathLen includes starting room
			if (len > max)
				max = len;
			path++;
		}
		nbMoves[filledMoves] = malloc(sizeof(int) * 2);
		nbMoves[filledMoves][0] = max;
		nbMoves[filledMoves][1] = i;
		filledMoves++;
	}

	for (int i = 0; i < filledMoves; i++) {
		printf("%d with id %d\n", nbMoves[i][0], nbMoves[i][1]);
	}

	int min = nbMoves[0][0], id = 0;
	for (int i = 1; i < filledMoves; i++) {
		if (nbMoves[i][0] < min) {
			min = nbMoves[i][0];
			id = nbMoves[i][1];
		}
	}

}