#ifndef LEM_IN_H
#define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include "lib.h"

# define	BUFFER_SIZE		1024
# define	STDIN			0
# define	STDOUT			1
# define	STDERR			2

typedef enum bool {
	false,
	true,
} bool;

typedef struct s_room {

	char			*name;
	int				x;
	int				y;
	int				type;	// 0 = normal, 1 = start, 2 = end
	char			**links;
	struct s_room	*prev;
	struct s_room	*next;
}	t_room;

typedef struct s_ant {

	int		id;
	t_room	*currRoom;

}	t_ant;

typedef struct s_data {

	t_room		*rooms;
	t_ant		*ants;
	int			nbAnts;
	int			nbRooms;

}	t_data;

int				get_next_line(int fd, char **line);

#endif