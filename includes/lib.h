#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# define	STDIN			0
# define	STDOUT			1
# define	STDERR			2
# define    RED "\e[1;31m"
# define    RESET "\e[0m"

int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int 	ft_strlen(char *str);
int		ft_strfree(char **ptr);

int	    ft_isspace(char c);
int     ft_strnoisspace(char *s);
int     ft_isdigit(char c);
int     ft_strisdigit(char *s);

char	*ft_memalloc(size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);

void    *ft_malloc(size_t sizeOf, size_t size);

char	**ft_pushback(char **tab, char *val);
char	**ft_split(char const *s, char c);

long int 	ft_atoi(char *s);

#endif