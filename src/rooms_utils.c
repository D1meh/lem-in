#include "../includes/lem_in.h"

t_link	*lastLink(t_link *links) {
	t_link	*ret = links;
	while (ret->next)
		ret = ret->next;
	return ret;
}

void	addLink(t_link **links, t_link *new) {
	if (*links) {
		t_link *last = lastLink(*links);
		last->next = new;
		new->prev = last;
	} else
		*links = new;
}

t_link	*initLink(t_room *node, int distance) {
	t_link	*new = ft_malloc(sizeof(t_link), 1);
	new->node = node;
	new->distance = distance;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

size_t	roomSizeList(t_room *rooms) {
	size_t	len = 0;
	while (rooms) {
		len++;
		rooms = rooms->next;
	}
	return len;
}

t_room	*createRoom(char *name, unsigned int x, unsigned int y, int type) {
	t_room *ret = ft_malloc(sizeof(t_room), 1);

	ret->name = name;
	ret->x = x;
	ret->y = y;
	ret->type = type;
	ret->visited = false;
	ret->score = 0;
	ret->nbOfLinks = 0;
	ret->links = NULL;
	// === test === //
	ret->linkss = NULL;
	// ============ //
	ret->distances = NULL;
	ret->prev = NULL;
	ret->next = NULL;
	return ret;
}

t_room	*lastRoom(t_room *roomList) {
	t_room	*ret = roomList;
	while (ret->next)
		ret = ret->next;
	return ret;
}

void	addRoom(t_room **roomList, t_room *new) {
	static int id = 0;
	new->id = id;
	id++;

	if (*roomList) {
		t_room *last = lastRoom(*roomList);
		last->next = new;
		new->prev = last;
	} else
		*roomList = new;
}

bool	validStartEnd(t_room *roomlist) {
	bool start = false, end = false;

	while (roomlist) {

		if (roomlist->type == 1) {
			if (start)
				exitError("Too many starts.\n");
			start = true;
		} else if (roomlist->type == 2) {
			if (end)
				exitError("Too many ends.\n");
			end = true;
		}

		roomlist = roomlist->next;
	}
	return start && end;
}

t_room	*findRoomByName(char *name, t_room *rooms) {
	while (rooms) {
		if (ft_strcmp(name, rooms->name) == 0)
			return (rooms);
		rooms = rooms->next;
	}
	return NULL;
}

void	browseRooms(t_room *roomList) {
	while (roomList) {
		printf("Room -> ID[%d]\t[name=%s]\t[x=%d][y=%d][visited=%d]\t%s\tLinks[", roomList->id, roomList->name, \
			roomList->x, roomList->y, roomList->visited, roomList->type == 2 ? "End" : roomList->type == 1 ? "Start" : "-");
		size_t i = 0;
		while (roomList->links && i < roomList->nbOfLinks)
			printf("'%s', ", roomList->links[i++]->name);
		if (!(roomList->links))
			printf("NULL]\n");
		else
			printf("\b\b]\n");
		roomList = roomList->next;
	}
}

void	addLinkForRoom(t_room *r, t_room *roomList, char *link) {
	t_room	**new = ft_malloc(sizeof(t_room *), (r->nbOfLinks + 2));
	int		*newDistances = ft_malloc(sizeof(int), (r->nbOfLinks + 1));
	size_t i = 0;

	while (i < r->nbOfLinks) {
		new[i] = r->links[i];
		i++;
	}
	while (roomList) {
		if (ft_strcmp(link, roomList->name) == 0) {
			t_link	*newLink = initLink(roomList, 1);
			addLink(&(r->linkss), newLink);
			new[i] = roomList;
			new[i + 1] = NULL;
			break ;
		}
		roomList = roomList->next;
	}
	for (size_t i = 0; i < (r->nbOfLinks + 1); i++)
		newDistances[i] = 1;
	free(r->links);
	if (r->distances)
		free(r->distances);
	r->links = new;
	r->distances = newDistances;
	r->nbOfLinks++;
}

bool avoidDoubleLink(t_room *room, char *link) {
	size_t i = 0;

	if (ft_strcmp(room->name, link) == 0)
		return false;
	while (i < room->nbOfLinks) {
		if (ft_strcmp(link, room->links[i]->name) == 0)
			return false;
		i++;
	}
	return true;
}

bool	avoidDoubeRoom(t_room *roomList, t_room *elt) {
	while (roomList) {
		if (ft_strcmp(roomList->name, elt->name) == 0 || (roomList->x == elt->x && roomList->y == elt->y))
			return false;
		roomList = roomList->next;
	}
	return true;
}

t_room	*getSpecificRoom(t_room *roomList, int type) {
	while (roomList) {
		if (roomList->type == type)
			return roomList;
		roomList = roomList->next;
	}
	return NULL;
}

t_room	*findRoomByPos(t_room *roomList, unsigned int x, unsigned int y) {
	while (roomList) {
		if (roomList->x == x && roomList->y == y) {
			return roomList;
		}
		roomList = roomList->next;
	}
	return NULL;
}