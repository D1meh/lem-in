#include "../includes/lem_in.h"
#include "../includes/visualizer.h"

#define WHEEL_SPEED 10

SDL_Color		grey = {105, 105, 105, 255};
SDL_Color		brown = {160, 82, 45, 255};
SDL_Color		black = {0, 0, 0, 255};
SDL_Color		orange = {255, 214, 135, 255};

SDL_Color		green = {81, 239, 86, 255};
SDL_Color		red = {255, 0, 0, 255};

typedef struct	s_visu {
	bool		leftButtonDown;
	SDL_Point	mousePos;
	SDL_Point	clickedPos;
	SDL_Point	dragged;
	SDL_Point	saved;
	SDL_Point	scale;

}	t_visu;

t_visu			visu;
t_data			anthill;

int		scaleX(x) {
	return x * (150 * 1 + visu.scale.x) + (visu.saved.x + visu.dragged.x);
}

int		scaleY(y) {
	return y * (150 * 1 + visu.scale.y) + (visu.saved.y + visu.dragged.y);
}

void	onMouseMove(SDL_Event events) {
	visu.mousePos.x = events.motion.x;
	visu.mousePos.y = events.motion.y;
	if (visu.leftButtonDown)
	{
		visu.dragged.x = visu.mousePos.x - visu.clickedPos.x;
		visu.dragged.y = visu.mousePos.y - visu.clickedPos.y;
	}
}

void	onClickUp(SDL_Event events) {
	if (visu.leftButtonDown && events.button.button == SDL_BUTTON_LEFT) {
		visu.saved.x += visu.dragged.x;
		visu.saved.y += visu.dragged.y;
		visu.dragged.x = 0;
		visu.dragged.y = 0;
		visu.leftButtonDown = false;
	}
}

void	onClickDown(SDL_Event events) {
	if (!visu.leftButtonDown && events.button.button == SDL_BUTTON_LEFT) {
		visu.leftButtonDown = true;
		visu.clickedPos.x = visu.mousePos.x;
		visu.clickedPos.y = visu.mousePos.y;
	}
}

void	onMouseWheel(SDL_Event events) {
	
	if (events.wheel.y > 0) {
		visu.scale.x += WHEEL_SPEED;
		visu.scale.y += WHEEL_SPEED;
	}
	else if (events.wheel.y < 0) {
		visu.scale.x -= WHEEL_SPEED;
		visu.scale.y -= WHEEL_SPEED;
	}
}

void eventLoop(SDL_Window *window, SDL_Renderer *renderer) {
	SDL_Event events;
	while (SDL_PollEvent(&events)) {
		switch (events.type)
		{
			case SDL_QUIT:
				ft_exit_with_sdl(false, window, renderer, "");
				break;
			case SDL_MOUSEMOTION:
				onMouseMove(events);
				break;
			case SDL_MOUSEWHEEL:
				onMouseWheel(events);
				break ;
			case SDL_MOUSEBUTTONDOWN:
				onClickDown(events);
				break ;
			case SDL_MOUSEBUTTONUP:
				onClickUp(events);
				break;
			default:
				break;
		}
	}
}

void	drawLinks(SDL_Renderer *renderer, t_room *rooms) {
	SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
	while (rooms) {
		t_link	*links = rooms->links;
		while (links) {
			SDL_RenderDrawLine(renderer, scaleX(rooms->x), scaleY(rooms->y), scaleX(links->node->x), scaleY(links->node->y));
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
		int radius = 20 * 1 + (visu.scale.y / 4);
		radius = radius < 5 ? 5 : radius;
		SDL_RenderFillCircle(renderer, scaleX(rooms->x), scaleY(rooms->y), radius);
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

int main(void) {
	SDL_Window		*window = NULL;
	SDL_Renderer	*renderer = NULL;

	anthill.maxX = 0;
    anthill.maxY = 0;
	anthill.nbRooms = 0;

	visu.leftButtonDown = false;

	char	**lines = readInput();
	parseLines(lines, &anthill);

	if (anthill.nbRooms > 1100)
	{
		exitError("Visualizer cannot preview more than 1000 rooms !\n");
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