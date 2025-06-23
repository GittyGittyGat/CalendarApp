#include "taskunit.h"

// task will be a button (click to expand)
// task will contain a rectangle to display string text
// task will contain a place to show priority and urgency (2 bubbles)
// task will contain tags and category


void taskunit::draw(SDL_Renderer*& renderer, TTF_Font*& font, TTF_Font*& font2) {

	//	i should worry about exact implementation later let's focus on what I have to do now
	//	start working on taskdisplay and circle render
	myButton.draw(renderer);
	urgCircle.draw(renderer);
	prioCircle.draw(renderer);

	if (!nameTexture) {
		float wid, hei;
		SDL_Surface* surface = TTF_RenderText_Solid(font, event.name.c_str(), 0, { 255, 255, 255, 255 });
		nameTexture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_DestroySurface(surface);
		if (SDL_GetTextureSize(nameTexture, &wid, &hei)) {
			std::cout << hei << " height\n";
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
		float wid, hei;
		if (SDL_GetTextureSize(descTexture, &wid, &hei)) {
			std::cout << hei << " height\n";
			ddescBox.w = std::min(ddescBox.w, wid);
			ddescBox.h = hei;
		}
		sdescBox.w = ddescBox.w;
		sdescBox.h = ddescBox.h;

	}

	SDL_RenderTexture(renderer, nameTexture, &snameBox, &dnameBox);
	SDL_RenderTexture(renderer, descTexture, &sdescBox, &ddescBox);

	return;
}