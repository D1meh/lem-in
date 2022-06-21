#ifndef LEM_IN_H
#define LEM_IN_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "lib.h"

# define	BUFFER_SIZE		1024
# define	STDIN			0
# define	STDOUT			1
# define	STDERR			2
# define	RED "\e[1;31m"
# define	RESET "\e[0m"

typedef enum bool {
	false,
	true,
} bool;

typedef struct s_room {

	char			*name;
	int				id;
	unsigned int	x;
	unsigned int	y;
	int				type;	// 0 = normal, 1 = start, 2 = end
	size_t			nbOfLinks;
	bool			visited;
	bool			used;
	struct s_room	**links;
	struct s_room	*prev;
	struct s_room	*next;
}	t_room;

typedef struct s_ant {

	int		id;
	t_room	*currRoom;

}	t_ant;

typedef struct s_data {

	t_room			*rooms;
	t_ant			*ants;
	long int		nbAnts;
	size_t			nbRooms;
	unsigned int	maxX;
	unsigned int	maxY;

}	t_data;

int		get_next_line(int fd, char **line);

void	exitError(char *error);
void	addRoom(t_room **roomList, t_room *new);
void	browseRooms(t_room *roomList);
void	pushbackRoom(t_room *r, t_room *roomList, char *link);

size_t	roomSizeList(t_room *rooms);
bool	avoidDoubleLink(t_room *room, char *link);
bool	validStartEnd(t_room *roomlist);
bool	avoidDoubeRoom(t_room *roomList, t_room *elt);
t_room	*createRoom(char *name, unsigned int x, unsigned int y, int type);
t_room	*lastRoom(t_room *roomList);
t_room	*findRoomByName(char *name, t_room *rooms);
t_room	*getSpecificRoom(t_room *roomList, int type);
t_room	*findRoomByPos(t_room *roomList, unsigned int x, unsigned int y);
t_room	***addToList(t_room ***pathList, t_room **path, int found);


t_room	**BFS(t_room *start, t_room *end, t_data *anthill);
void	BFSForStartNeighbours(t_room ***pathList);
void	algo(t_data *anthill);

#endif