#include "circledraw.h"
#include <iostream>

void circledraw::draw(SDL_Renderer*& renderer) const {
	float x = 0, y = -radius, midpoint = radius;
	SDL_SetRenderDrawColor(renderer, circleColor.r, circleColor.g, circleColor.b, circleColor.a);
	// draw diamond:
	//while (x < -y) {
	//	if (midpoint > 0) {
	//		y++;
	//		midpoint += 2 * (centerX + centerY) + 1;
	//	}
	//	else {
	//		midpoint += 2 * centerX + 1;
	//	}
	while (x < -y) {
		if (midpoint > 0) {
			y++;
			midpoint += 2 * (x + y) + 1;
		}
		else {
			midpoint += 2 * x + 1;
		}
		//std::cout << x << " " << y << '\n';
		//std::cin.ignore();  std::cin.get();
		//SDL_RenderLine(renderer, centerX + x, centerY + y, centerX - x, centerY - y);
		SDL_RenderLine(renderer, centerX + x, centerY + y, centerX - x, centerY + y);
		SDL_RenderLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
		SDL_RenderLine(renderer, centerX + y, centerY + x, centerX - y, centerY + x);
		SDL_RenderLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

		x++;
	}
	SDL_SetRenderDrawColor(renderer, 255, 251, 201, 255);
	return;
}

/*
		SDL_RenderLine(renderer, x, y, x + pointx, y + pointy);
		SDL_RenderLine(renderer, x, y, x - pointx, y + pointy);
		SDL_RenderLine(renderer, x, y, x + pointx, y - pointy);
		SDL_RenderLine(renderer, x, y, x - pointx, y - pointy);
		SDL_RenderLine(renderer, x, y, x + pointy, y + pointx);
		SDL_RenderLine(renderer, x, y, x - pointy, y + pointx);
		SDL_RenderLine(renderer, x, y, x + pointy, y - pointx);
		SDL_RenderLine(renderer, x, y, x - pointy, y - pointx);
		
*/