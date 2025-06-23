#pragma once
//#include <SDL3/SDL.h>
#include "database/eventStructs.h"
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
	//std::string name = "hello Wolrd"; // temp -> will use event for it later
	//std::string desc = "this is my random desc"; // temp -> will use event for it later
	button myButton;
	SDL_Texture* nameTexture = nullptr;
	SDL_Texture* descTexture = nullptr;
	eventTable event;
	circledraw urgCircle;
	circledraw prioCircle;
public:
	//placement starts with 0 for the first item
	taskunit(void(*func)(std::string), /*const eventTable& eT,*/ const int& placement, const float& width, eventTable& eT) :myButton(func)
	{
		float y = 0;
		event = eT;
		if (placement) {
			y = (placement * (BUTTON_SPACING + BUTTON_HEIGHT)) + BUTTON_SPACING + BUTTON_SPACE_BUFFE;
			myButton.update(BUTTON_SPACING, y);
			std::cout << placement * (2 * BUTTON_SPACING + BUTTON_HEIGHT) << '\n';
		}
		else {
			y = (BUTTON_SPACING + BUTTON_SPACE_BUFFE);
			myButton.update(BUTTON_SPACING, y);
			std::cout << BUTTON_SPACING << '\n';
		}
		myButton.update(width);
		event.name += std::to_string(placement);

		urgCircle.update(width - 20 - BUTTON_SPACING, y + 15, 10, { 0, 255, 255, 255 });
		prioCircle.update(width - 45 - BUTTON_SPACING, y + 15, 10, { 255, 0, 255, 255 });

		dnameBox = { (float)myButton.getX(), (float)myButton.getY(), (float)width, FONTSIZE};
		ddescBox = { (float)myButton.getX(), (float)myButton.getY() + 38, (float)width, FONTSIZE };


	}
	
	void draw(SDL_Renderer*& renderer, TTF_Font*& font, TTF_Font*& font2);

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
		myButton.incrementY(y);
		prioCircle.incrementY(y);
		urgCircle.incrementY(y);
	}
	inline bool hasIntersection(const SDL_FRect* mouse) {
		return myButton.hasIntersection(mouse);
	}
	inline void clicked() const {
		myButton.onClick(event.notes);
	}
	~taskunit() {}
};

