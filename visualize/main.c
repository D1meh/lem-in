#include "../includes/lem_in.h"
#include "../includes/visualizer.h"

SDL_Color		grey = {105, 105, 105, 255};
SDL_Color		brown = {160, 82, 45, 255};
SDL_Color		black = {0, 0, 0, 255};
SDL_Color		orange = {255, 214, 135, 255};

SDL_Color		green = {81, 239, 86, 255};
SDL_Color		red = {255, 0, 0, 255};

t_data			anthill;

int		scaleX(int x, t_visu *visu) {
	return x * (150 * 1 + visu->scale.x) + (visu->saved.x + visu->dragged.x);
}

int		scaleY(int y, t_visu *visu) {
	return y * (150 * 1 + visu->scale.y) + (visu->saved.y + visu->dragged.y);
}

void eventLoop(SDL_Window *window, SDL_Renderer *renderer, t_visu *visu) {
	SDL_Event events;
	while (SDL_PollEvent(&events)) {
		switch (events.type)
		{
			case SDL_QUIT:
				ft_exit_with_sdl(false, window, renderer, "");
				break;
			case SDL_MOUSEMOTION:
				onMouseMove(events, visu);
				break;
			case SDL_MOUSEWHEEL:
				onMouseWheel(events, visu);
				break ;
			case SDL_MOUSEBUTTONDOWN:
				onClickDown(events, visu);
				break ;
			case SDL_MOUSEBUTTONUP:
				onClickUp(events, visu);
				break;
			default:
				break;
		}
	}
}

void	drawLinks(SDL_Renderer *renderer, t_room *rooms, t_visu *visu) {
	SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
	while (rooms) {
		t_link	*links = rooms->links;
		while (links) {
			SDL_RenderDrawLine(renderer, scaleX(rooms->x, visu), scaleY(rooms->y, visu), scaleX(links->node->x, visu), scaleY(links->node->y, visu));
			links = links->next;
		}
		rooms = rooms->next;
	}
}

void	drawRooms(SDL_Renderer *renderer, t_room *rooms, t_visu *visu) {

	while (rooms) {
		// Set the renderer color
		if (rooms->type == 1)
			SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);
		else if (rooms->type == 2)
			SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
		else
			SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
		int radius = 20 * 1 + (visu->scale.y / 4);
		radius = radius <= 5 ? 5 : radius;
		SDL_RenderFillCircle(renderer, scaleX(rooms->x, visu), scaleY(rooms->y, visu), radius);
		rooms = rooms->next;
	}
}

int main(void) {
	SDL_Window		*window = NULL;
	SDL_Renderer	*renderer = NULL;

	t_visu			visu;
	t_data			anthill;
	anthill.maxX = 0;
    anthill.maxY = 0;
	anthill.nbRooms = 0;

	visu.leftButtonDown = false;

	char	**lines = readInput();
	parseLines(lines, &anthill);

	if (anthill.nbRooms > 1100) {
		exitError("Visualizer cannot load more than 1000 rooms !\n");
		return 0;
	}

	/* Init SDL and renderer */
	window = initSDL(window, renderer);
	renderer = initRenderer(window, renderer);

	/* Infinite game loop */
	while (true) {
		setBackGroundColor(window, renderer, brown);

		eventLoop(window, renderer, &visu);

		drawRooms(renderer, anthill.rooms, &visu);
		drawLinks(renderer, anthill.rooms, &visu);

		/* Render the actual image */
		SDL_RenderPresent(renderer);
	}

	ft_exit_with_sdl(false, window, renderer, "");
	return 0;
}