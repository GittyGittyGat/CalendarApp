#include "taskunit.h"

// task will be a button (click to expand)
// task will contain a rectangle to display string text
// task will contain a place to show priority and urgency (2 bubbles)
// task will contain tags and category

#ifndef NULL
#define NULL 0
#endif


void taskunit::getDrawData(std::vector<std::vector<SDL_FPoint>>& circleData, std::vector<SDL_FRect>& rectData) {

	//	i should worry about exact implementation later let's focus on what I have to do now
	//	start working on taskdisplay and circle render
	//if (!render) {
	//	return;
	//}

	myButton.getDrawData(rectData);
	urgCircle.getDrawData(circleData);
	prioCircle.getDrawData(circleData);

	return;
}

void taskunit::drawText(SDL_Renderer* renderer, TTF_Font* font, TTF_Font* font2, std::vector<SDL_Texture*>&zeroToNine)
{
	float wid, hei;
	if (!nameTexture) {
		SDL_Surface* surface = TTF_RenderText_Solid(font, event.name.c_str(), 0, { 255, 255, 255, 255 });
		nameTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_DestroySurface(surface);
		if (SDL_GetTextureSize(nameTexture, &wid, &hei)) {
			dnameBox.w = std::min(dnameBox.w, wid);
			dnameBox.h = hei;
		}
		snameBox.w = dnameBox.w;
		snameBox.h = dnameBox.h;
	}
	if (!descTexture) {
		SDL_Surface* surface = TTF_RenderText_Solid(font2, event.description.c_str(), 0, { 255, 255, 255, 255 });
		descTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_DestroySurface(surface);
		if (SDL_GetTextureSize(descTexture, &wid, &hei)) {
			ddescBox.w = std::min(ddescBox.w, wid);
			ddescBox.h = hei;
		}
		sdescBox.w = ddescBox.w;
		sdescBox.h = ddescBox.h;

	}

	if (zeroToNine[event.priority]) {
		SDL_GetTextureSize(zeroToNine[event.priority], &wid, &hei);
		prioBox.w = wid; prioBox.h = hei;
		SDL_RenderTexture(renderer, zeroToNine[event.priority], NULL, &prioBox);
	}
	if (zeroToNine[event.urgency]) {
		SDL_GetTextureSize(zeroToNine[event.urgency], &wid, &hei);
		urgBox.w = wid; urgBox.h = hei;
		SDL_RenderTexture(renderer, zeroToNine[event.urgency], NULL, &urgBox);
	}
	SDL_RenderTexture(renderer, nameTexture, &snameBox, &dnameBox);
	SDL_RenderTexture(renderer, descTexture, &sdescBox, &ddescBox);
}

taskunit::taskunit(const int& placement, const float& width, eventTable& eT)
{

	float y = 0;
	event = eT;
	if (placement) {
		y = (placement * (BUTTON_SPACING + BUTTON_HEIGHT)) + BUTTON_SPACING + BUTTON_SPACE_BUFFE;
		myButton.update(BUTTON_SPACING, y);
		//std::cout << placement * (2 * BUTTON_SPACING + BUTTON_HEIGHT) << '\n';
	}
	else {
		y = (BUTTON_SPACING + BUTTON_SPACE_BUFFE);
		myButton.update(BUTTON_SPACING, y);
		//std::cout << BUTTON_SPACING << '\n';
	}
	myButton.update(width);
	event.name += std::to_string(placement);

	urgCircle.update(width - 20 - BUTTON_SPACING, y + 15, 10);
	prioCircle.update(width - 45 - BUTTON_SPACING, y + 15, 10);
	urgBox = { width - 22 - BUTTON_SPACING, y + 10, 10, 10 };
	prioBox = { width - 46 - BUTTON_SPACING - 2, y + 10, 10, 10 };

	dnameBox = { (float)myButton.getX() + 7, (float)myButton.getY(), (float)width, FONTSIZE };
	ddescBox = { (float)myButton.getX() + 7, (float)myButton.getY() + 38, (float)width, FONTSIZE };

}

void taskunit::swipe(SDL_FRect* mouseNew, SDL_FRect* mouseOld)
{
	incrementX((mouseNew->x - mouseOld->x) - (myButton.getX() - BUTTON_SPACING));
}