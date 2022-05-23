#ifndef LEM-IN_H
#define LEM-IN_H

typedef struct s_room {

	char	*name;
	int		x;
	int		y;
	int		start_or_end;	// 0 = normal, 1 = start, 2 = end
	struct s_room	*prev;
	struct s_room	*next;
}	t_room;

#endif