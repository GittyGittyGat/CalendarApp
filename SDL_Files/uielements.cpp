#include "uielements.h"

std::vector<SDL_FRect> uiDrawRects;

//SDL_Color barColor = { 0x00, 0x3B, 0x46, 255 };
//SDL_Color buttonColors = { 0xFF, 0x8C, 0x94, 255 };
SDL_Color barColor = { 0xFF, 0xFF, 0xFF, 255 };
SDL_Color buttonColors = { 0x00, 0x00, 0x00, 255 };
SDL_Color backGroundColorNew = { 0x23, 0x23, 0x23, 255 };



uielements::uielements() {
	lowBar.x = 0; lowBar.y = 680; lowBar.h = 40; lowBar.w = 480;
	tasksButton.update(6, 685, 152, 30);
	timerButton.update(164, 685, 152, 30);
	settingsButton.update(322, 685, 152, 30);
}

void uielements::draw(SDL_Renderer* renderer) {
	if (uiDrawRects.size() == 0) {
		uiDrawRects.push_back(lowBar);
		tasksButton.getDrawData(uiDrawRects);
		timerButton.getDrawData(uiDrawRects);
		settingsButton.getDrawData(uiDrawRects);
	}

	SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
	SDL_RenderFillRect(renderer, &uiDrawRects[0]);
	SDL_SetRenderDrawColor(renderer, buttonColors.r, buttonColors.g, buttonColors.b, buttonColors.a);
	SDL_RenderFillRects(renderer, &uiDrawRects[1], (int)uiDrawRects.size() - 1);
	SDL_SetRenderDrawColor(renderer, backGroundColorNew.r, backGroundColorNew.g, backGroundColorNew.b, backGroundColorNew.a);
	
}

unsigned int uielements::checkClicks(SDL_FRect* mouse) {
	if (tasksButton.hasIntersection(mouse)) {
		return static_cast<unsigned int>(DISP_TASKS + 1);
	}
	else if (timerButton.hasIntersection(mouse)) {
		return static_cast<unsigned int>(DISP_TIMER + 1);
	}
	else if (settingsButton.hasIntersection(mouse)) {
		return static_cast<unsigned int>(DISP_SETTINGS + 1);
	}
	return 0;
}