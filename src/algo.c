#include "../includes/lem_in.h"

void    algo(t_data *anthill) {
    // On trouve le nombre de chemin max
    // Si le nombre de fourmis est inferieur au nombre de chemins trouvé :
    // On reduit le nombre de chemin au nombre de fourmis
    // D'abord definir un max selon
    // le nombre de depart sur start et le nombre de depart sur end

    t_room *start = getSpecificRoom(anthill->rooms, 1);
    t_room *end = getSpecificRoom(anthill->rooms, 2);

    int maxPossibilities = 0;
    if (start->nbOfLinks >= end->nbOfLinks)
        maxPossibilities = end->nbOfLinks;
    else
        maxPossibilities = start->nbOfLinks;

    printf("maxPossibilities: %d\n", maxPossibilities);



}