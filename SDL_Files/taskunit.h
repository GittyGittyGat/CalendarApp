#pragma once
//#include <SDL3/SDL.h>
#include "../database/eventStructs.h"
#include "button.h"
#include "circledraw.h"
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
#include <algorithm>
// task will be a button (click to expand) and show more information
// task will contain a rectangle to display string text
// task will contain a place to show priority and urgency (2 bubbles)
// task will contain tags and category

const float FONTSIZE = 36;

class taskunit
{
private:
	//if (SDL_GetTextureSize(texture, &texW, &texH)) {
	//	texRect.h = texH;
	//	texRect.w = texW;
	//}
	SDL_FRect dnameBox;
	SDL_FRect ddescBox;
	SDL_FRect snameBox = { 0, 0, 0, 0 };
	SDL_FRect sdescBox = { 0, 0, 0, 0 };
	SDL_FRect urgBox = { 0, 0, 0, 0 };
	SDL_FRect prioBox = { 0, 0, 0, 0 };
	//std::string name = "hello Wolrd"; // temp -> will use event for it later
	//std::string desc = "this is my random desc"; // temp -> will use event for it later
	button myButton;
	SDL_Texture* nameTexture = nullptr;
	SDL_Texture* descTexture = nullptr;
	SDL_Texture* priorityTexture = nullptr;
	SDL_Texture* urgencyTexture = nullptr;
	eventTable event;
	circledraw urgCircle;
	circledraw prioCircle;
public:
	bool render = false;
	//placement starts with 0 for the first item
	taskunit(const int& placement, const float& width, eventTable& eT);
	
	void getDrawData(std::vector <std::vector<SDL_FPoint>>& circleData, std::vector<SDL_FRect>& rectData);
	void drawText(SDL_Renderer* renderer, TTF_Font* font, TTF_Font* font2, std::vector<SDL_Texture*>& zeroToNine);
	eventTable* getEventTable() {
		return &event;
	}
	void update(const float& width) {
		myButton.update(width);
		dnameBox.w = width;
		ddescBox.w = width;
		SDL_DestroyTexture(nameTexture); nameTexture = nullptr;
		SDL_DestroyTexture(descTexture); descTexture = nullptr;
	}
	void inline incrementY(const float& y) {
		dnameBox.y += y;
		ddescBox.y += y;
		urgBox.y += y;
		prioBox.y += y;
		myButton.incrementY(y);
		prioCircle.incrementY(y);
		urgCircle.incrementY(y);
	}
	void inline incrementX(const float& x) {
		dnameBox.x += x;
		ddescBox.x += x;
		urgBox.x += x;
		prioBox.x += x;
		myButton.incrementX(x);
		prioCircle.incrementX(x);
		urgCircle.incrementX(x);
	}
	void swipe(SDL_FRect* mouseNew, SDL_FRect* mouseOld);
	inline bool hasIntersection(const SDL_FRect* mouse) {
		return myButton.hasIntersection(mouse);
	}
	~taskunit() {}
};