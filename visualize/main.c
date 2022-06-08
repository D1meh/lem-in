#include "../includes/lem_in.h"
#include "../sdl2/include/SDL2/SDL.h"

void    ft_exit_with_sdl(bool isError, SDL_Window *window, SDL_Renderer *renderer) {
    if (isError) {
        const char    *sdlError = SDL_GetError();
        write(STDERR, "SDL_ERROR : ", 12);
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

int main(void) {
    SDL_Window      *window = NULL;
    SDL_Renderer    *renderer = NULL;
    // SDL_Color orange = {255, 127, 40, 255};

    /* Init SDL */
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        ft_exit_with_sdl(true, window, renderer);

    /* Create SDL Window */
    window = SDL_CreateWindow("lem-in", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE);
    if(window == NULL)
        ft_exit_with_sdl(true, window, renderer);

    SDL_MaximizeWindow(window);
    SDL_ShowWindow(window);

    /* Le renderer utilise l’accélération matérielle. Les données sont en mémoire vidéo, plus rapide que la mémoire vive. */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer)
        ft_exit_with_sdl(true, window, renderer);
    
    SDL_Delay(3000);
    ft_exit_with_sdl(false, window, renderer);
    return 0;
}