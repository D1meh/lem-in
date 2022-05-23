#include "../includes/lib.h"

int	ft_strcmp(char *s1, char *s2) {
	return (*s1 != *s2 || *s1 == 0 || *s2 == 0 ? *s1 - *s2 : ft_strcmp(s1+1, s2+1));
}

int ft_strncmp(char *s1, char *s2, int n) {
	return (*s1 != *s2 || *s1 == 0 || *s2 == 0 || n <= 0 ? *s1 - *s2 : ft_strncmp(s1+1, s2+1, n-1));
}
