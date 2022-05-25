#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../includes/lem_in.h"

char *randomName() {
    size_t length = 5;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    char *randomName = NULL;

    randomName = malloc(sizeof(char) * (length + 1));
    if (!randomName)
        return NULL;

    for (size_t n = 0 ; n < length ; n++) {
        int index = rand() % (int)(sizeof(charset) -1);
        randomName[n] = charset[index];
    }

    randomName[length] = '\0';

    return randomName;
}

/* ./map_generator number_of_node */
int main(int ac, char **av) {
    if (ac >= 2) {
        if (!ft_strisdigit(av[1]))
        {
            exitError("Wrong parameters for generator\n");
        }
        char    *filename = ft_strjoin(av[1], "_generated.map");
        int     fd = open(filename, O_CREAT | O_TRUNC | O_RDWR);

        int     len = ft_atoi(av[1]);
        unsigned int x = 0;
        unsigned int y = 0;
        unsigned int maxX = sqrt((double)(len));
        unsigned int maxY = sqrt((double)(len));
        while (len--) {
            printf("%s %u %u\n", randomName(), x, y);

        }

    }
    return (0);
}