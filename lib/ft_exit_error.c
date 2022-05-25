#include "../includes/lib.h"

void    exitError(char *error) {
    write(STDERR, RED, ft_strlen(RED));
    write(STDERR, "ERROR\n", 6);
    write(STDERR, error, ft_strlen(error));
    write(STDERR, RESET, ft_strlen(RESET));
    system("leaks lem-in");
    exit(EXIT_FAILURE);
}
