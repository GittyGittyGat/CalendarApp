#include "circledraw.h"
#include <iostream>


void circledraw::getDrawDataOutline(std::vector<SDL_FPoint>& vec, int degrees)
{
	float x = 0, y = -radius, midpoint = -radius;
	while (x < -y) {
		if (midpoint > 0) {
			y += 1; midpoint += 2 * (x + y) + 1;
		}
		else {
			midpoint += 2 * x + 1;
		}

		vec.push_back({	centerX + x, centerY + y});
		vec.push_back({ centerX - x, centerY + y });
		vec.push_back({ centerX + x, centerY - y });
		vec.push_back({ centerX - x, centerY - y });
		vec.push_back({ centerX + y, centerY + x });
		vec.push_back({ centerX - y, centerY + x });
		vec.push_back({ centerX + y, centerY - x });
		vec.push_back({ centerX - y, centerY - x });
		x++;
	}
	return;
}


void circledraw::getDrawData(std::vector<std::vector<SDL_FPoint>>& circleData) const {
	float x = 0, y = -radius, midpoint = radius;
	static std::vector<SDL_FPoint> circleVector;
	circleVector.clear();
	while (x < -y) {
		if (midpoint > 0) {
			y++;
			midpoint += 2 * (x + y) + 1;
		}
		else {
			midpoint += 2 * x + 1;
		}
		circleVector.push_back({ centerX + x, centerY + y });
		circleVector.push_back({ centerX - x, centerY - y });
		circleVector.push_back({ centerX + x, centerY - y });
		circleVector.push_back({ centerX + y, centerY + x });
		circleVector.push_back({ centerX - y, centerY + x });
		circleVector.push_back({ centerX - y, centerY - x });
		circleVector.push_back({ centerX + y, centerY - x });
		circleVector.push_back({ centerX - x, centerY + y });
		x++;
	}
	circleData.push_back(circleVector);
	return;
}

/*
		This Along Side diamond draw gave a cool visual so saving it for now :) 
		---------------
		SDL_RenderLine(renderer, x, y, x + pointx, y + pointy);
		SDL_RenderLine(renderer, x, y, x - pointx, y + pointy);
		SDL_RenderLine(renderer, x, y, x + pointx, y - pointy);
		SDL_RenderLine(renderer, x, y, x - pointx, y - pointy);
		SDL_RenderLine(renderer, x, y, x + pointy, y + pointx);
		SDL_RenderLine(renderer, x, y, x - pointy, y + pointx);
		SDL_RenderLine(renderer, x, y, x + pointy, y - pointx);
		SDL_RenderLine(renderer, x, y, x - pointy, y - pointx);
		
*/

// PROPER CIRCLE DRAW: (current code is similar to this but without duplicates)

		/*
		circleVector.push_back({ centerX + x, centerY + y }); // 1
		circleVector.push_back({ centerX - x, centerY - y }); // 2
		circleVector.push_back({ centerX + x, centerY + y }); // 3
		circleVector.push_back({ centerX - x, centerY + y }); // 4
		circleVector.push_back({ centerX - x, centerY - y }); // 5
		circleVector.push_back({ centerX + x, centerY - y }); // 6
		circleVector.push_back({ centerX + y, centerY + x }); // 7
		circleVector.push_back({ centerX - y, centerY + x }); // 8
		circleVector.push_back({ centerX - y, centerY - x }); // 9
		circleVector.push_back({ centerX + y, centerY - x }); // 10
		*/

		// draw diamond instead of circle (oops):
		//while (x < -y) {
		//	if (midpoint > 0) {
		//		y++;
		//		midpoint += 2 * (centerX + centerY) + 1;
		//	}
		//	else {
		//		midpoint += 2 * centerX + 1;
		//	}