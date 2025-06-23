#pragma once
#include <SDL3/SDL.h>

class circledraw
{
private:
	float centerX = 0, centerY = 0, radius = 0;
	SDL_Color circleColor = {0, 0, 0, 0};

public:
	circledraw() {}
	circledraw(const float& xpos, const float& ypos, const float& rad, const SDL_Color& color) {
		centerX = xpos; centerY = ypos, radius = rad; circleColor = color;
	}
	void draw(SDL_Renderer*& renderer) const;
	void update(const float& xpos, const float& ypos, const SDL_Color& color) {
		centerX = xpos; centerY = ypos, circleColor = color;
	}
	void update(const float& xpos, const float& ypos, const float& rad, const SDL_Color& color) {
		centerX = xpos; centerY = ypos, radius = rad; circleColor = color;
	}
	void update(const float& xpos, const float& ypos) {
		centerX = xpos; centerY = ypos;
	}
	void incrementY(const float& ypos) {
		centerY += ypos;
	}
};

