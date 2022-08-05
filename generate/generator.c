#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../includes/lem_in.h"

#define linksNumb 3;

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
    char            *part1 = NULL;
    char            *cx = NULL;
    char            *cy = NULL;
    char            **tabNames = NULL;
    bool            endPrinted = false;
    unsigned int    x = 0;
    unsigned int    y = 0;

    write(fd, "##start\n", 8);
    while (y < maxY) {
        while (x < maxX) {
            if (y >= ceil(maxY - 1) && x >= ceil(maxX - 1) && !endPrinted) {
                endPrinted = true;
                write(fd, "##end\n", 6);
            }
            cx = ft_itoa(x);
            cy = ft_itoa(y);
            part1 = ft_strjoin(cx, "_");
            name = ft_strjoin(part1, cy);
            free(cx);
            free(cy);
            free(part1);
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
    while (tabNames[i]) {

		int numberOfLinks = rand() % linksNumb; // Number between 1 and 2 links
		numberOfLinks += 1;
		while (numberOfLinks--) {
			int	randIdx = rand() % len;
			write(fd, tabNames[i], ft_strlen(tabNames[i]));
            write(fd, "-", 1);
            write(fd, tabNames[randIdx], ft_strlen(tabNames[randIdx]));
            write(fd, "\n", 1);
		}
        i++;
    }
}

int main(int ac, char **av) {
	srand(time(NULL));

    if (ac < 2)
        exitError("Generator: Bad argument for generator.\n");
    if (!ft_strisdigit(av[1]))
        exitError("Generator: need a number of node as argument\n");

    unsigned int    len = ft_atoi(av[1]);
    char            *name = ft_strjoin(av[1], "_generated.map");
    if (len < 50 || len > 10000)
        exitError("Generator: need a number between 50 and 10000\n");
    char            *filename = ft_strjoin("./maps/", name);
    int             fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
    unsigned int    maxX = ceil(sqrt((double)(len)));
    unsigned int    maxY = ceil(sqrt((double)(len)));

    char            **tabNames = NULL;
    char            *nbAnts = ft_itoa(100);

    
    /* === output nb of ants === */
    write(fd, nbAnts, ft_strlen(nbAnts));
    write(fd, "\n", 1);

    /* === output all nodes === */
    tabNames = generateAllNodes(fd, maxX, maxY);

    /* === output all links === */
    generateAllLinks(fd, len, tabNames);

    close(fd);
    free(nbAnts);
    free(filename);
    free(name);
    system("leaks generator");
    return (0);
}
