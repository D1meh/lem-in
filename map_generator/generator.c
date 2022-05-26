#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../includes/lem_in.h"

// typedef struct s_data {
//     char    **tabNames;
// }   t_data;

char *randomName() {
    size_t length = 20;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
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

void  generateNode(int fd, char *name, unsigned int x, unsigned int y) {
    char *itx = ft_itoa(x);
    char *ity = ft_itoa(y);
    char *posX = ft_strjoin(itx, " ");
    char *posY = ft_strjoin(ity, "\n");
    write(fd, name, ft_strlen(name));
    write(fd, " ", 1);
    write(fd, posX, ft_strlen(posX));
    write(fd, posY, ft_strlen(posY));
    free(posX);
    free(posY);
    free(itx);
    free(ity);
}

char    **generateAllNodes(int fd, unsigned int maxX, unsigned int maxY) {
    char            *name = NULL;
    char            **tabNames = NULL;
    bool            endPrinted = false;
    unsigned int    x = 0;
    unsigned int    y = 0;

    write(fd, "##start\n", 8);
    while (y < maxY) {
        while (x < maxX) {
            if (y >= ceil(maxY / 2) && x >= ceil(maxX / 2) && !endPrinted) {
                endPrinted = true;
                write(fd, "##end\n", 6);
            }
            name = randomName();
            tabNames = ft_pushback(tabNames, name);
            generateNode(fd, name, x, y);
            free(name);
            x++;
        }
        x = 0;
        y++;
    }
    return tabNames;
}

void    generateAllLinks(int fd, unsigned int len, char **tabNames) {
    
    unsigned int i = 0;
    unsigned int l = ceil(sqrt((double)(len)));
    while (tabNames[i]) {
        if (tabNames[i] && tabNames[i + 1])
        {
            write(fd, tabNames[i], ft_strlen(tabNames[i]));
            write(fd, "-", 1);
            write(fd, tabNames[i + 1], ft_strlen(tabNames[i + 1]));
            write(fd, "\n", 1);
        }
        if (tabNames[i] && i + l < len && tabNames[i + l]) {
            write(fd, tabNames[i], ft_strlen(tabNames[i]));
            write(fd, "-", 1);
            write(fd, tabNames[i + l], ft_strlen(tabNames[i + l]));
            write(fd, "\n", 1);
        }
        i++;
    }
}

int main(int ac, char **av) {
    if (ac < 2)
        exitError("Generator: Bad argument for generator.\n");
    if (!ft_strisdigit(av[1]))
        exitError("Generator: need a number of node as argument\n");

    unsigned int    len = ft_atoi(av[1]);
    char            *name = ft_strjoin(av[1], "_generated.map");
    if (len < 50 || len > 10000)
        exitError("Generator: need a number between 50 and 10000\n");
    char            *filename = ft_strjoin("./maps/", name);
    int             fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 777);
    unsigned int    maxX = ceil(sqrt((double)(len)));
    unsigned int    maxY = ceil(sqrt((double)(len)));

    char            **tabNames = NULL;
    char            *nbAnts = ft_itoa(floor(len / 5));

    
    /* === output nb of ants === */
    write(fd, nbAnts, ft_strlen(nbAnts));
    write(fd, "\n", 1);

    /* === output all nodes === */
    tabNames = generateAllNodes(fd, maxX, maxY);

    /* === output all links === */
    generateAllLinks(fd, len, tabNames);

    /* === end === */
    write(fd, "\n", 1);

    close(fd);
    free(nbAnts);
    free(filename);
    free(name);

    return (0);
}