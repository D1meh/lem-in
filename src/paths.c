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
		toAdd = ft_malloc(sizeof(int), size);
		for (int i = 0; i < size; i++) {
			toAdd[i] = arr[i];
		}
		newTab = ft_malloc(sizeof(int *), (len+1));
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

void findComb(int arr[], int index, int n, int reducedN, size_t *size) {
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

void initFindComb(int n, size_t *size) {
	int arr[n];
	findComb(arr, 0, n, n, size);
}

void getOptimalPath(t_data *anthill, t_path *pathList, size_t nbOfPath) {
	size_t sizeOfTab = 0, ants = anthill->nbAnts;
	int osef[1];	// variable inutile juste pour avoir un param dans getFinalTab

	// Finding all the possible combinations that gives the number of ants
	initFindComb(ants, &sizeOfTab);
	int **tab = getFinalTab(osef, RET, 0);
	//printFinalTab(tab, sizeOfTab, ants);

	int **nbMoves = ft_malloc(sizeof(int *), (int)sizeOfTab);
	int filledMoves = 0;
	for (size_t i = 0; i < sizeOfTab; i++) {

		size_t sum = 0, j = 0, path = 0;

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
		t_path *tmp = pathList;
		for (int k = j-1; k >= 0; k--) {
			int len = pathLen(tmp->path) + tab[i][k] - 1; // minus 2 because pathLen includes starting room
			if (len > max)
				max = len;
			path++;
			tmp = tmp->next;
		}
		nbMoves[filledMoves] = ft_malloc(sizeof(int), 2);
		nbMoves[filledMoves][0] = max;
		nbMoves[filledMoves][1] = i;
		filledMoves++;
	}

	int min = nbMoves[0][0], id = nbMoves[0][1];
	for (int i = 1; i < filledMoves; i++) {
		if (nbMoves[i][0] < min) {
			min = nbMoves[i][0];
			id = nbMoves[i][1];
		}
	}

	// printf("min : len = %d, id = %d references to: ", min, id);
	// for (int sum = 0, i = 0; sum < ants; i++) {
	// 	printf("%d ", tab[id][i]);
	// 	sum += tab[id][i];
	// }
	// printf("\n");
	
	printer(anthill, pathList, tab[id]);
	for (int i = 0; i < filledMoves; i++)
		free(nbMoves[i]);
	free(nbMoves);
}