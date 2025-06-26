#pragma once
#include <SDL3/SDL.h>
#include <vector>

class circledraw
{
private:
	float centerX = 0, centerY = 0, radius = 0;

public:
	circledraw() {}
	inline circledraw(const float& xpos, const float& ypos, const float& rad) {
		centerX = xpos; centerY = ypos, radius = rad;;
	}
	void getDrawData(std::vector<std::vector<SDL_FPoint>>& circleData) const;
	inline void update(const float& xpos, const float& ypos, const float& rad) {
		centerX = xpos; centerY = ypos, radius = rad;
	}
	inline void update(const float& xpos, const float& ypos) {
		centerX = xpos; centerY = ypos;
	}
	inline void incrementY(const float& ypos) {
		centerY += ypos;
	}
	inline void incrementX(const float& xpos) {
		centerX += xpos;
	}
	void getDrawDataOutline(std::vector<SDL_FPoint>&, int degrees);
};

