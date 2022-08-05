#include "../includes/lem_in.h"
#include "../includes/visualizer.h"

void    ft_exit_with_sdl(bool isError, SDL_Window *window, SDL_Renderer *renderer, char *funcName) {
    if (isError) {
        const char    *sdlError = SDL_GetError();
        write(STDERR, funcName, ft_strlen(funcName));
        write(STDERR, " : ", 3);
        write(STDERR, sdlError, ft_strlen((char*)sdlError));
        write(STDERR, "\n", 1);
    }
    if (window != NULL)
        SDL_DestroyWindow(window);
    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    SDL_Quit();
    if (isError)
        exit(EXIT_FAILURE);
    else
        exit(EXIT_SUCCESS);
}

void setBackGroundColor(SDL_Window *window, SDL_Renderer *renderer, SDL_Color color) {
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0)
       ft_exit_with_sdl(true, window, renderer, "SDL_SetRenderDrawColor");
    if(SDL_RenderClear(renderer) != 0)
        ft_exit_with_sdl(true, window, renderer, "SDL_RenderClear");
}

SDL_Window	*initSDL(SDL_Window *window, SDL_Renderer *renderer) {
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_exit_with_sdl(true, window, renderer, "SDL_Init");

	/* Create SDL Window */
	window = SDL_CreateWindow("lem-in", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(window == NULL)
		ft_exit_with_sdl(true, window, renderer, "SDL_CreateWindow");

	/* Maximize and show window */
	SDL_MaximizeWindow(window);
	SDL_SetWindowSize(window, 1920, 1080);
	SDL_ShowWindow(window);
	return window;
}

SDL_Renderer	*initRenderer(SDL_Window *window, SDL_Renderer *renderer) {
	/* Le renderer utilise l’accélération matérielle. Les données sont en mémoire vidéo, plus rapide que la mémoire vive. */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
		ft_exit_with_sdl(true, window, renderer, "SDL_CreateRenderer");
	return renderer;
}

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;
    while (offsety >= offsetx) {
        SDL_RenderDrawLine(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
        SDL_RenderDrawLine(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
        SDL_RenderDrawLine(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
        SDL_RenderDrawLine(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);
        if (status < 0) {
            status = -1;
            break;
        }
        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
    return 0;
}