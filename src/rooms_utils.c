#include "../includes/lem_in.h"

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
	ret->used = false;
	ret->visited = false;
	ret->nbOfLinks = 0;
	ret->links = NULL;
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
		t_room *elt = lastRoom(*roomList);
		elt->next = new;
		new->prev = elt;
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
		printf("Room -> ID[%d]\t[name=%s]\t[x=%d][y=%d]\t%s\tLinks[", roomList->id, roomList->name, \
			roomList->x, roomList->y, roomList->type == 2 ? "End" : roomList->type == 1 ? "Start" : "-");
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

void	pushbackRoom(t_room *r, t_room *roomList, char *link) {
	t_room **ret = ft_malloc(sizeof(t_room*), (r->nbOfLinks + 1));
	size_t i = 0;

	while (i < r->nbOfLinks) {
		ret[i] = r->links[i];
		i++;
	}
	while (roomList) {
		if (ft_strcmp(link, roomList->name) == 0) {
			ret[i] = roomList;
			break ;
		}
		roomList = roomList->next;
	}
	free(r->links);
	r->links = ret;
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