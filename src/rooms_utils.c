#include "../includes/lem_in.h"

t_room	*createRoom(char *name, int x, int y, int type) {
	t_room *ret = ft_malloc(sizeof(t_room), 1);

	ret->name = name;
	ret->x = x;
	ret->y = y;
	ret->type = type;
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
		printf("Room -> Name[%s][%d][%d]\t%s\tLinks[", roomList->name, roomList->x, roomList->y, roomList->type == 2 ? "End" : roomList->type == 1 ? "Start" : "Middle");
		int i = 0;
		while (roomList->links && roomList->links[i])
			printf("'%s', ", roomList->links[i++]);
		if (!(roomList->links))
			printf("NULL]\n");
		else
			printf("\b\b]\n");
		roomList = roomList->next;
	}
}

bool avoidDoubleLink(t_room *room, char *link) {
	int i = 0;

	while (room->links && room->links[i]) {
		if (ft_strcmp(room->links[i], link) == 0 || ft_strcmp(room->name, link) == 0)
			return false;
		i++;
	}
	return true;
}

bool	noDouble(t_room *roomList, t_room *elt) {
	while (roomList) {
		if (ft_strcmp(roomList->name, elt->name) == 0 || (roomList->x == elt->x && roomList->y == elt->y))
			return false;
		roomList = roomList->next;
	}
	return true;
}
