#include "../includes/lib.h"

int ft_isdigit(char *s) {
	int i = 0;

	while (s[i]) {
		if (s[i] > '9' || s[i] < '0')
			return 0;
		i++;
	}
	return 1;
}