#include "../includes/lem_in.h"

t_room	*createRoom(char *name, int x, int y, int type) {
	t_room *ret = ft_malloc(sizeof(t_room), 1);

	ret->name = name;
	ret->x = x;
	ret->y = y;
	ret->type = type;
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
				ft_exit_error("Too many starts\n");
			start = true;
		} else if (roomlist->type == 2) {
			if (end)
				ft_exit_error("Too many ends\n");
			end = true;
		}

		roomlist = roomlist->next;
	}
	return start && end;
}

void	browseRooms(t_room *roomList) {
	while (roomList) {
		printf("-> %s : x=%d, y=%d, type=%d\n", roomList->name, roomList->x, roomList->y, roomList->type);
		roomList = roomList->next;
	}
}