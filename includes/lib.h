#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>

int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int 	ft_strlen(char *str);
int		ft_strfree(char **ptr);

char	*ft_memalloc(size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);


#endif