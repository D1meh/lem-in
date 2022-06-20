#include "../includes/lem_in.h"
#include "../lib/sdl2/include/SDL2/SDL.h"

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

// void drawCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color)
// {
//     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
//     for (int w = 0; w < radius * 2; w++)
//     {
//         for (int h = 0; h < radius * 2; h++)
//         {
//             int dx = radius - w; // horizontal offset
//             int dy = radius - h; // vertical offset
//             if ((dx*dx + dy*dy) <= (radius * radius))
//             {
//                 SDL_RenderDrawPoint(renderer, x + dx, y + dy);
//             }
//         }
//     }
// }

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

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

void setBackGroundColor(SDL_Renderer *renderer, SDL_Color color) {
    /* 
    ** The rendered is kinda of a color pencil and we can set it to
    ** differents colors so we can draw with differents colors
    ** Here we transform our rendered to an orange (example) pen the rendered paint in orange
    */
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0)
        return ;

    /* Clear permet de peindre sur l'ensemble de la fenetre */
    if(SDL_RenderClear(renderer) != 0)
        return ;
}

void eventLoop(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Event events;
    while (SDL_PollEvent(&events)){
        if (events.type == SDL_QUIT)
            ft_exit_with_sdl(false, window, renderer, "");
        if (events.type == SDL_KEYDOWN) {
            printf("Key down -> %c\n", (events.key.keysym.scancode + 'a' - 4));
            if (events.key.keysym.sym == SDLK_ESCAPE) {
                ft_exit_with_sdl(false, window, renderer, "");
            }
        }
        if (events.type == SDL_MOUSEBUTTONDOWN)
            ;
    }
}

int main(void) {
	printf("Visualizer working !\n");
    SDL_Window      *window = NULL;
    SDL_Renderer    *renderer = NULL;
    SDL_Color       grey = {105, 105, 105, 255};
    SDL_Color       black = {0, 0, 0, 255};
    SDL_Color       orange = {255, 214, 135, 255};
	SDL_Color		brown = {160, 82, 45, 255};

    /* Init SDL */
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        ft_exit_with_sdl(true, window, renderer, "SDL_Init");

    /* Create SDL Window */
    window = SDL_CreateWindow("lem-in", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window == NULL)
        ft_exit_with_sdl(true, window, renderer, "SDL_CreateWindow");
    
    /* Maximize and show window */
    SDL_MaximizeWindow(window);
    SDL_ShowWindow(window);

    /* Le renderer utilise l’accélération matérielle. Les données sont en mémoire vidéo, plus rapide que la mémoire vive. */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
        ft_exit_with_sdl(true, window, renderer, "SDL_CreateRenderer");

    // SDL_Rect rectangle = {100, 100, 100, 100};
    // SDL_Rect square = {250, 100, 100, 100};
    while (true) {
        eventLoop(window, renderer);
        setBackGroundColor(renderer, brown);

        /* Draw a rectangle */
        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
        SDL_RenderFillCircle(renderer, 100, 100, 10);
		SDL_RenderFillCircle(renderer, 200, 100, 10);
		SDL_RenderFillCircle(renderer, 300, 100, 10);
    
        /* Render the actual image */
        SDL_RenderPresent(renderer);
    }

    ft_exit_with_sdl(false, window, renderer, "");
    return 0;
}