#include "../includes/lib.h"

// int	ft_strcmp(char *s1, char *s2) {
	
// 	int i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return s1[i] - s2[i];
// }

// int ft_strncmp(char *s1, char *s2, int n) {

// 	int i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n-1)
// 		i++;
// 	return s1[i] - s2[i];
// }

int	ft_strcmp(char *s1, char *s2) {
	return (*s1 != *s2 || *s1 == 0 || *s2 == 0 ? *s1 - *s2 : ft_strcmp(s1+1, s2+1));
}

int ft_strncmp(char *s1, char *s2, int n) {
	return (*s1 != *s2 || *s1 == 0 || *s2 == 0 || n <= 0 ? *s1 - *s2 : ft_strncmp(s1+1, s2+1, n-1));
}