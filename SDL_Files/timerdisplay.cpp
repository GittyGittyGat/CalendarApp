#include "timerdisplay.h"
#include <string>
#include <iostream>
SDL_Color timerCircleColor{ 255, 255, 255, 255};

SDL_Texture* timeTex = nullptr;;
SDL_Surface* timeSurf = nullptr;
std::string timeStr;

void timerdisplay::draw(SDL_Renderer* renderer, TTF_Font* font) {
	static unsigned long long previousTime = 0;
	if (!timerPoints.size())
		timerCircle.getDrawDataOutline(timerPoints, 0);

	SDL_SetRenderDrawColor(renderer, timerCircleColor.r, timerCircleColor.g, timerCircleColor.b, timerCircleColor.a);
	SDL_RenderPoints(renderer, timerPoints.data(), (int)timerPoints.size());

	
	long long timeRemaining = timerTimeRemaining - (SDL_GetTicks() - timeTimeStarted);
	timeRemaining /= 1000;

	if (timeRemaining <= 0) {
		if (tState == TIMER_STARTED){
			prevTState = TIMER_BREAK;
			tState = TIMER_PAUSED;
			timerTimeRemaining = (5LL * 1000 * 60) + 500;
			timeRemaining = timerTimeRemaining;
			timeTimeStarted = SDL_GetTicks();
		}
		else if(tState == TIMER_BREAK){
			prevTState = TIMER_STARTED;
			tState = TIMER_PAUSED;
			timerTimeRemaining = 30 * 1000 * 60 + 500;
			timeRemaining = timerTimeRemaining;
			timeTimeStarted = SDL_GetTicks();
		}
		timeStr = "00:00";
		SDL_DestroyTexture(timeTex);
		timeSurf = TTF_RenderText_Solid(font, timeStr.c_str(), 0, { 255, 255, 255, 255 });
		timeTex = SDL_CreateTextureFromSurface(renderer, timeSurf);
		SDL_DestroySurface(timeSurf);
	}

	if (tState == TIMER_STARTED || tState == TIMER_BREAK) {
		if (timeRemaining != previousTime) {
			if (timeTex) {
				SDL_DestroyTexture(timeTex);
			}
			timeStr.clear();
			if ((timeRemaining / 60) < 10) {
				timeStr += '0';
			}
			timeStr += std::to_string(timeRemaining / 60);
			timeStr += ":";
			if ((timeRemaining % 60) < 10) {
				timeStr += '0';
			}
			timeStr += std::to_string(timeRemaining % 60);
			timeSurf = TTF_RenderText_Solid(font, timeStr.c_str(), 0, { 255, 255, 255, 255 });
			timeTex = SDL_CreateTextureFromSurface(renderer, timeSurf);
			SDL_DestroySurface(timeSurf);
			previousTime = timeRemaining;
		}
	}

	SDL_RenderTexture(renderer, timeTex, NULL, &timeDestBox);
	
}

void timerdisplay::checkClick(SDL_FRect* mouse) {
	if (SDL_HasRectIntersectionFloat(mouse, &startTimerBox)) {
		if (tState == NOT_STARTED) {
			tState = TIMER_STARTED;
			timerTimeRemaining = 1000*30*60 + 500;
			timeTimeStarted = SDL_GetTicks();
		}
		else if(tState == TIMER_STARTED) {
			prevTState = TIMER_STARTED;
			tState = TIMER_PAUSED;
			timerTimeRemaining = timerTimeRemaining - (SDL_GetTicks() - timeTimeStarted);
		}
		else if(tState == TIMER_PAUSED){
			tState = prevTState;
			timeTimeStarted = SDL_GetTicks();
		}
		else if (tState == TIMER_BREAK) {
			tState = TIMER_PAUSED;
			prevTState = TIMER_BREAK;
			timerTimeRemaining = timerTimeRemaining - (SDL_GetTicks() - timeTimeStarted);
		}
	}
}