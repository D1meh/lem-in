#include "../includes/lem_in.h"
#include "../includes/visualizer.h"

SDL_Color		grey = {105, 105, 105, 255};
SDL_Color		brown = {160, 82, 45, 255};
SDL_Color		black = {0, 0, 0, 255};
SDL_Color		orange = {255, 214, 135, 255};

SDL_Color		green = {81, 239, 86, 255};
SDL_Color		red = {255, 0, 0, 255};

int		scaleX(int x, t_visu *visu) {
	return x * (150 * 1 + visu->scale.x) + (visu->saved.x + visu->dragged.x);
}

int		scaleY(int y, t_visu *visu) {
	return y * (150 * 1 + visu->scale.y) + (visu->saved.y + visu->dragged.y);
}

void eventLoop(SDL_Window *window, SDL_Renderer *renderer, t_visu *visu, solveStep **steps, t_data *anthill) {
	SDL_Event events;
	while (SDL_PollEvent(&events)) {
		switch (events.type)
		{
			case SDL_QUIT:
				ft_exit_with_sdl(false, window, renderer, "", anthill, *steps);
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
			case SDL_KEYDOWN:
				switch (events.key.keysym.sym)
				{
					case SDLK_RIGHT:
						if ((*steps) && (*steps)->next)
							(*steps) = (*steps)->next;
						break;
					case SDLK_LEFT:
						if ((*steps) && (*steps)->prev)
							(*steps) = (*steps)->prev;
						break;
					case SDLK_ESCAPE:
						ft_exit_with_sdl(false, window, renderer, "", anthill, *steps);
					break;
				}
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

void	drawAnts(SDL_Renderer *renderer, t_room *rooms, t_visu *visu, solveStep *steps) {
	// (void)renderer; (void)rooms; (void)visu; (void)steps;
	
	if (steps) {
		for (int i = 0; i < steps->antsByStep ; i++) {
			if (ft_atoi(&steps->ants[i].id[1]) % 3 == 0)
				SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
			else if (ft_atoi(&steps->ants[i].id[1]) % 2 == 0)
				SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a);
			else
				SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);
			t_room	*room = findRoomByName(steps->ants[i].roomName, rooms);

			int radius = 10 * 1 + (visu->scale.y / 4);
			radius = radius <= 2 ? 2 : radius;
			SDL_RenderFillCircle(renderer, scaleX(room->x, visu), scaleY(room->y, visu), radius);

		}
	}
}

t_data	*initStructs(t_visu *visu) {
	t_data	*anthill = ft_malloc(sizeof(t_data), 1);
	anthill->maxX = 0;
	anthill->maxY = 0;
	anthill->nbRooms = 0;

	visu->leftButtonDown = false;
	visu->saved.x = 0;
	visu->saved.y = 0;
	visu->scale.x = 0;
	visu->scale.y = 0;
	visu->dragged.x = 0;
	visu->dragged.y = 0;
	return (anthill);
}

int main(void) {
	SDL_Window		*window = NULL;
	SDL_Renderer	*renderer = NULL;

	solveStep		*steps = NULL;
	t_data			*anthill;
	t_visu			visu;

	anthill = initStructs(&visu);

	// Read map
	char	**lines = readInput();
	parseLines(lines, anthill);
	

	// Read solution
	char	**solution = readInput();
	parseSolution(solution, &steps, anthill);


	if (anthill->nbRooms > 1100) {
		exitError("Visualizer cannot load more than 1000 rooms !\n");
		return 0;
	}

	/* Init SDL and renderer */
	window = initSDL(window, renderer);
	renderer = initRenderer(window, renderer);
	/* Infinite game loop */
	int i = 0;
	while (true) {
		eventLoop(window, renderer, &visu, &steps, anthill);
		setBackGroundColor(window, renderer, brown);

		drawLinks(renderer, anthill->rooms, &visu);
		drawRooms(renderer, anthill->rooms, &visu);

		drawAnts(renderer, anthill->rooms, &visu, steps);
		/* Render the actual image */
		SDL_RenderPresent(renderer);
		i++;
	}
	

	ft_exit_with_sdl(false, window, renderer, "", anthill, steps);
	return 0;
}
