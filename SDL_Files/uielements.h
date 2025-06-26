#pragma once
#include <SDL3/SDL.h>
#include "button.h"
#include <iostream>

enum displayScreens { DISP_TASKS, DISP_TIMER, DISP_SETTINGS, DISP_COMPLETE_TASK};


class uielements
{
	SDL_FRect lowBar;
	button tasksButton;
	button timerButton;
	button settingsButton;
	
public:

	unsigned int checkClicks(SDL_FRect* mouse);
	uielements();
	void draw(SDL_Renderer* renderer);

};

