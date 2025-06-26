#pragma once
#include "taskdisplay.h"
#include "settingsdisplay.h"
#include "uielements.h"
#include "timerdisplay.h"
#include "completeTaskDisplay.h"
class display
{
private:
	SDL_Renderer* renderer;
	TTF_Font *font1, *font2, *font3;

	displayScreens screenToDisplay = DISP_TASKS;
	taskdisplay appTaskDisp;
	settingsdisplay appSettingsDisp;
	uielements appUI;
	timerdisplay appTimerDisp;
	completeTaskDisplay appTaskDetails;

	// window related pointers

public:
	display(SDL_Renderer* rend, TTF_Font* f1, TTF_Font* f2, TTF_Font* f3);
	void changeDisplayScreen(const displayScreens& screen) {
		screenToDisplay = screen;
	}
	void draw();
	void checkClicks(SDL_FRect* mouse);
	void scroll(const float& direction) {
		if (screenToDisplay == DISP_TASKS) {
			appTaskDisp.incrementY(direction);
		}
	}

};

