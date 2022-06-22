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