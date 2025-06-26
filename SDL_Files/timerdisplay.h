#pragma once
#include "circledraw.h"
#include <SDL3_ttf/SDL_ttf.h>

enum timerStates { NOT_STARTED, TIMER_STARTED, TIMER_PAUSED, TIMER_BREAK};

class timerdisplay
{
private:
	circledraw timerCircle;
	std::vector<SDL_FPoint> timerPoints;
	SDL_FRect startTimerBox = {140, 260, 200, 200};
	SDL_FRect timeDestBox = {240 - 41, 360 - 20, 82, 40};
	timerStates tState = NOT_STARTED; timerStates prevTState = NOT_STARTED;
	long long timerTimeRemaining = 1000*30*60 + 500;
	long long timeTimeStarted = 0;
public:
	timerdisplay() {
		timerCircle.update(240, 360, 100); // change to height, width /2
	}
	void checkClick(SDL_FRect* mouse);
	void draw(SDL_Renderer* renderer, TTF_Font* font); // for now fixed 30min and 5mins
};

