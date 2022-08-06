#ifndef VISUALIZER_H
# define VISUALIZER_H

#include "../lib/sdl2/include/SDL2/SDL.h"

#define WHEEL_SPEED 5
#define ANIMATION_SPEED 4

typedef struct	s_visu {

	bool		leftButtonDown;
	SDL_Point	mousePos;
	SDL_Point	clickedPos;
	SDL_Point	dragged;
	SDL_Point	saved;
	SDL_Point	scale;

}	t_visu;

typedef struct s_Ant {

	char			*id;
	char			*roomName;

	long int		wantedX;
	long int		wantedY;

	long int		currX;
	long int		currY;

} Ant;

typedef struct s_solveStep {

	int					antsByStep;
	Ant					*ants;

	struct s_solveStep	*prev;
	struct s_solveStep	*next;

} solveStep;

void			ft_exit_with_sdl(bool isError, SDL_Window *window, SDL_Renderer *renderer, char *funcName, t_data *anthill, solveStep *steps);
void			setBackGroundColor(SDL_Window *window, SDL_Renderer *renderer, SDL_Color color);
int				SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);
SDL_Window		*initSDL(SDL_Window *window, SDL_Renderer *renderer);
SDL_Renderer	*initRenderer(SDL_Window *window, SDL_Renderer *renderer);

// Mouse Handle
void			onMouseMove(SDL_Event events, t_visu *visu);
void			onClickUp(SDL_Event events, t_visu *visu);
void			onClickDown(SDL_Event events, t_visu *visu);
void			onMouseWheel(SDL_Event events, t_visu *visu);

// Parse
bool			parseSolution(char **solution, solveStep **steps, t_data *anthill);

#endif