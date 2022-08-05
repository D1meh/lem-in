#include "../../includes/lib.h"

void	ft_putstr_fd(int fd, char *s) {
	int i = 0;
	while (s[i]) {
		write(fd, &s[i], 1);
		i++;
	}
}