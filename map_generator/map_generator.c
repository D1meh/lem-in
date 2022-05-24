#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../includes/lem_in.h"

char *randomName() {
    size_t length = 5;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    char *randomName = NULL;

    randomName = malloc(sizeof(char) * (length + 1));
    if (!randomName)
        return NULL;

    for (int n = 0 ; n < length ; n++) {
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
        int len = ft_atoi(av[1]);

    }
    return (0);
}