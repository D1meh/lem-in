#include "../includes/lem_in.h"
#include "../includes/visualizer.h"

SDL_Color		grey = {105, 105, 105, 255};
SDL_Color		brown = {160, 82, 45, 255};
SDL_Color		black = {0, 0, 0, 255};
SDL_Color		orange = {255, 214, 135, 255};

SDL_Color		green = {81, 239, 86, 255};
SDL_Color		red = {255, 0, 0, 255};

int		scale(x) {
	return x * 110 + 50;
} 

void eventLoop(SDL_Window *window, SDL_Renderer *renderer) {
	SDL_Event events;
	while (SDL_PollEvent(&events)) {
		if (events.type == SDL_QUIT)
			ft_exit_with_sdl(false, window, renderer, "");
		if (events.type == SDL_KEYDOWN) {
			printf("Key down -> %i\n", (events.key.keysym.sym));
			if (events.key.keysym.sym == SDLK_ESCAPE) {
				ft_exit_with_sdl(false, window, renderer, "");
			}
		}
		if (events.type == SDL_MOUSEBUTTONDOWN)
			;
	}
}

void	drawLinks(SDL_Renderer *renderer, t_room *rooms) {
	SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
	while (rooms) {
		t_link	*links = rooms->links;
		while (links) {
			SDL_RenderDrawLine(renderer, scale(rooms->x), scale(rooms->y), scale(links->node->x), scale(links->node->y));
			SDL_RenderDrawLine(renderer, scale(rooms->x) + 1, scale(rooms->y), scale(links->node->x) + 1, scale(links->node->y));
			SDL_RenderDrawLine(renderer, scale(rooms->x) - 1, scale(rooms->y), scale(links->node->x) - 1, scale(links->node->y));
			SDL_RenderDrawLine(renderer, scale(rooms->x), scale(rooms->y) + 1, scale(links->node->x), scale(links->node->y) + 1);
			SDL_RenderDrawLine(renderer, scale(rooms->x), scale(rooms->y) - 1, scale(links->node->x), scale(links->node->y) - 1);
			links = links->next;
		}
		rooms = rooms->next;
	}
}

void	drawRooms(SDL_Renderer *renderer, t_room *rooms) {

	while (rooms) {
		// Set the renderer color
		if (rooms->type == 1)
			SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);
		else if (rooms->type == 2)
			SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
		else
			SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
		SDL_RenderFillCircle(renderer, scale(rooms->x), scale(rooms->y), 20);
		rooms = rooms->next;
	}
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
	SDL_SetWindowSize(window, 900, 900);
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

int main(void) {
	SDL_Window		*window = NULL;
	SDL_Renderer	*renderer = NULL;
    t_data			anthill;
	anthill.maxX = 0;
    anthill.maxY = 0;
	anthill.nbRooms = 0;

	char	**lines = readInput();
	parseLines(lines, &anthill);

	if (anthill.nbRooms > 100)
	{
		exitError("Visualizer cannot preview more than 50 rooms !\n");
		return 0;
	}

	/* Init SDL and renderer */
	window = initSDL(window, renderer);
	renderer = initRenderer(window, renderer);
	while (true) {
		eventLoop(window, renderer);

		setBackGroundColor(window, renderer, brown);
		drawRooms(renderer, anthill.rooms);
		drawLinks(renderer, anthill.rooms);

		/* Render the actual image */
		SDL_RenderPresent(renderer);
	}

	ft_exit_with_sdl(false, window, renderer, "");
	return 0;
}