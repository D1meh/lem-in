#include "../../includes/lib.h"

static int tabLen(char **tab) {
	int i = 0;
	if (!tab) return 0;
	while (tab[i]) i++;
	return i;
}

char	**ft_pushback(char **tab, char *val) {
	int len = tabLen(tab);
	char **ret = ft_malloc(sizeof(char *), (len + 2));
	int i = 0;

	while (i < len) {
		ret[i] = tab[i];
		i++;
	}
	if (tab)
		free(tab);
	ret[i] = ft_strdup(val);
	ret[i + 1] = NULL;
	return ret;
}
