#include "../includes/lib.h"

static int tabLen(char **tab) {
	int i = 0;
	if (!tab) return 0;
	while (tab[i]) i++;
	return i;
}

char	**ft_pushback(char **tab, char *val) {
	char **ret = malloc(sizeof(char*) * (tabLen(tab) +2 ));
	int i = 0;

	while (i < tabLen(tab)) {
		ret[i] = tab[i];
		i++;
	}
	free(tab);
	ret[i] = val;
	ret[i+1] = NULL;
	return ret;
}