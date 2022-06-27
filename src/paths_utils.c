#include "../includes/lem_in.h"

int	pathLen(t_room **path) {
	return (*path == 0 ? 0 : pathLen(path+1) + 1);
}

int nbOfPath(t_room ***pathList) {
	int i = 0;
	while (pathList[i]) i++;
	return i;
}

t_room ***orderPath(t_room ***pathList) {
	for (int i = 1; pathList[i]; i++) {
		t_room **a = pathList[i];
		int b = i;
		while (b > 0 && pathLen(pathList[b-1]) > pathLen(a)) {
			pathList[b] = pathList[b-1];
			b--;
		}
		pathList[b] = a;
	}
	return pathList;
}

t_path	*lastPath(t_path *paths) {
	t_path	*ret = paths;
	while (ret->next)
		ret = ret->next;
	return ret;
}

void	addPath(t_path **paths, t_path *new) {

	if (*paths) {
		t_path *last = lastPath(*paths);
		last->next = new;
		new->prev = last;
	}
	else
		*paths = new;
}

t_path	*initPath(t_room **roomPath) {
	t_path	*new = malloc(sizeof(t_path) * 1);
	new->path = roomPath;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

// t_room ***addToList(t_room ***pathList, t_room **path, int found) {

// 	t_room ***newList = malloc(sizeof(t_room **) * (found + 2));

// 	int i = 0;
// 	while (i < found) {
// 		newList[i] = pathList[i];
// 		i++;
// 	}
// 	newList[i] = path;
// 	newList[i + 1] = NULL;
// 	if (pathList)
// 		free(pathList);
// 	return newList;
// }

t_room **initPrev(size_t size) {
	t_room	**prev = malloc(sizeof(t_room *) * (size + 1));

	size_t	i = 0;
	while (i < size) {
		prev[i] = NULL;
		i++;
	}
	prev[size] = NULL;
	return prev;
}

void printPaths(t_path *paths) {
	printf("-------- printPaths --------\n");
	if (!paths) return;
	while (paths) {
		printQueue(paths->path);
		paths = paths->next;
		if (paths)
			printf("------------------------\n");
	}
}

void	markPath(t_room *start, t_room *end, t_room **path) {
	size_t	i = 0;
	size_t	len = queueSize(path);
	while (i < len) {
		if (start != path[i] && end != path[i])
			// path[i]->used = true;
			path[i]->score += 1;
			// if (path[i]->score > 2)
			// 	path[i]->used = true;
		i++;
	}
}

void	resetVisited(t_room *rooms) {
	while (rooms) {
		rooms->visited = false;
		rooms = rooms->next;
	}
}