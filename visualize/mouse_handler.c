#include "../includes/lem_in.h"
#include "../includes/visualizer.h"

void	onMouseMove(SDL_Event events, t_visu *visu) {
	visu->mousePos.x = events.motion.x;
	visu->mousePos.y = events.motion.y;
	if (visu->leftButtonDown)
	{
		visu->dragged.x = visu->mousePos.x - visu->clickedPos.x;
		visu->dragged.y = visu->mousePos.y - visu->clickedPos.y;
	}
}

void	onClickUp(SDL_Event events, t_visu *visu) {
	if (visu->leftButtonDown && events.button.button == SDL_BUTTON_LEFT) {
		visu->saved.x += visu->dragged.x;
		visu->saved.y += visu->dragged.y;
		visu->dragged.x = 0;
		visu->dragged.y = 0;
		visu->leftButtonDown = false;
	}
}

void	onClickDown(SDL_Event events, t_visu *visu) {
	if (!visu->leftButtonDown && events.button.button == SDL_BUTTON_LEFT) {
		visu->leftButtonDown = true;
		visu->clickedPos.x = visu->mousePos.x;
		visu->clickedPos.y = visu->mousePos.y;
	}
}

void	onMouseWheel(SDL_Event events, t_visu *visu) {
	
	if (events.wheel.y > 0) {
		visu->scale.x += WHEEL_SPEED;
		visu->scale.y += WHEEL_SPEED;
	}
	else if (events.wheel.y < 0) {
		visu->scale.x -= WHEEL_SPEED;
		visu->scale.y -= WHEEL_SPEED;
	}
}
