#ifndef VISUALIZER_H
# define VISUALIZER_H

#include "../lib/sdl2/include/SDL2/SDL.h"

void    ft_exit_with_sdl(bool isError, SDL_Window *window, SDL_Renderer *renderer, char *funcName);
void	setBackGroundColor(SDL_Window *window, SDL_Renderer *renderer, SDL_Color color);
int		SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

#endif