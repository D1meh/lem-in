#include "../includes/lib.h"

int ft_isspace(char *s) {
	int i = 0;

	while (s[i]) {
		if (s[i] != '\n' && s[i] != ' ' && s[i] != '\t' && s[i] != '\r' && s[i] != '\r')
			return 0;
		i++;
	}
	return 1;
}