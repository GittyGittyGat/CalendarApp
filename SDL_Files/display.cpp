#include "display.h"

std::vector<SDL_Texture*> zeroToNine;

void initZeroToNine(SDL_Renderer* renderer, TTF_Font* font)
{
	zeroToNine.resize(10);
	for (int i = 0; i < 10; i++) {
		SDL_Surface* surface = TTF_RenderText_Solid(font, std::to_string(i).data(), 1, { 255, 255, 255, 255 });
		zeroToNine[i] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_DestroySurface(surface);
	}
}

display::display(SDL_Renderer* rend, TTF_Font* f1, TTF_Font* f2, TTF_Font* f3) : appTaskDisp("tasksdb.db")
{
	renderer = rend; font1 = f1; font2 = f2; font3 = f3;
	initZeroToNine(renderer, font3);
	appTaskDisp.fetchDataBase();
}

void display::draw()
{
	switch (screenToDisplay) {
	case DISP_TASKS:
		appTaskDisp.draw(renderer, font1, font2, zeroToNine);
		break;
	case DISP_TIMER:
		appTimerDisp.draw(renderer, font1);
		break;
	case DISP_SETTINGS:
		break;
	}
	appUI.draw(renderer);

}

void display::checkClicks(SDL_FRect* mouse)
{
	unsigned int clicked = 0;
	switch (screenToDisplay) {
	case DISP_TASKS:
		clicked = appTaskDisp.checkClick(mouse);
		if (clicked) {
			std::cout << appTaskDisp.getEventTable(clicked - 1)->name << '\n';
			screenToDisplay = DISP_COMPLETE_TASK;
		}
		break;
	case DISP_TIMER:
		appTimerDisp.checkClick(mouse);
		break;
	case DISP_SETTINGS:
		//check settings buttons
		break;
	case DISP_COMPLETE_TASK:
		break;
	}
	if (!clicked) {
		clicked = appUI.checkClicks(mouse);
		if (clicked) {
			screenToDisplay = static_cast<enum displayScreens>(clicked - 1);
		}
	}
}
