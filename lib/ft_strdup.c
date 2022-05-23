#include "../includes/lib.h"

static void ft_strcpy(char *dst, char *src) {
	while ((*dst++ = *src++));
}

char *ft_strdup(char *src) {
	char *dest = malloc(sizeof(char) * ft_strlen(src) + 1); ft_strcpy(dest, src); return dest;	
}