#include "../includes/lib.h"

static int ft_isdigit_char(char c) {
	return (c > '9' || c < '0' ? 0 : 1);
}

static int retarded_atoi(char *s) {
	int n = 0; while (ft_isdigit_char(*s)) {n = n * 10 + *s++ - '0';} return n;
}

int ft_atoi(char *s) {
	return (s[0] == '-') ? retarded_atoi(++s) * -1 : retarded_atoi(s);
}