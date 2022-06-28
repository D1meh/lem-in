#include "../includes/lem_in.h"

int	pathLen(t_room **path) {
	return (*path == 0 ? 0 : pathLen(path+1) + 1);
}

int nbOfPath(t_path *paths) {
	if (!paths)
		return 0;

	int i = 0;
	while (paths) {
		i++;
		paths = paths->next;
	}
	return i;
}

t_path	*orderPath(t_path *paths) {
	t_path *ret = NULL, *curr = paths;
	t_path **tmpTab = malloc(sizeof(t_path *) * (nbOfPath(paths) + 1));

	int i = 0;
	while (curr) {
		tmpTab[i] = initPath(curr->path);
		curr = curr->next;
		i++;
	}
	tmpTab[i] = NULL;

	for (int j = 1; tmpTab[j]; j++) {
		t_path *a = tmpTab[j];
		int b = j;
		while (b > 0 && pathLen(tmpTab[b-1]->path) > pathLen(a->path)) {
			tmpTab[b] = tmpTab[b-1];
			b--;
		}
		tmpTab[b] = a;
	}

	for (int j = 0; tmpTab[j]; j++) {
		addPath(&ret, tmpTab[j]);
	}
	free(tmpTab);
	deletePath(paths);
	return ret;
}

t_path	*lastPath(t_path *paths) {
	t_path	*ret = paths;
	while (ret->next) {
		ret = ret->next;
	}
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

void deletePath(t_path *paths) {
	while (paths) {
		t_path *tmp = paths->next;
		free(paths);
		paths = tmp;
	}
}

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