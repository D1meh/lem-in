#ifndef LEM_IN_H
# define LEM_IN_H

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

# define START 1
# define END 2

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
	size_t			score;
	struct s_room	**links;
	struct s_room	*prev;
	struct s_room	*next;
}	t_room;

typedef struct s_path {

	t_room			**path;
	struct s_path	*next;
	struct s_path	*prev;

}	t_path;

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


// ===== PARSER ===== //
int		get_next_line(int fd, char **line);
void    freeTab(char **tab);
void	printMap(t_data *anthill);
void    storeNbAnts(char *line, t_data *anthill);
bool	storeRoom(char *line, int type, t_data *anthill);
bool    storeLinks(char *line, t_data *anthill);
void    parseLines(char **lines, t_data *anthill);
char    **readInput();

// ===== ROOM UTILS ===== //
void	exitError(char *error);
void	addRoom(t_room **roomList, t_room *new);
void	browseRooms(t_room *roomList);
void	pushbackRoom(t_room *r, t_room *roomList, char *link);
int		pathLen(t_room **path);
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

// ===== PATH UTILS ===== //
int		pathLen(t_room **path);
int		nbOfPath(t_room ***pathList);
t_room	***orderPath(t_room ***pathList);
void	addPath(t_path **paths, t_path *new);
void	printPaths(t_path *paths);
void	markPath(t_room *start, t_room *end, t_room **path);
void	resetVisited(t_room *rooms);
t_room	**initPrev(size_t size);
// t_room	***addToList(t_room ***pathList, t_room **path, int found);
t_path	*initPath(t_room **roomPath);

// ===== ALGORITHM ===== //
t_room	**BFS(t_room *start, t_room *end, t_data *anthill);
void	BFSForStartNeighbours(t_room ***pathList);
void	solve(t_data *anthill);
void	getOptimalPath(t_data *anthill, t_room ***pathList, int nbOfPath);
void	printQueue(t_room **queue);
size_t	queueSize(t_room **queue);

#endif