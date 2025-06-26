#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <functional>
#include <vector>

// temporary definition as the project comes together
const float BUTTON_HEIGHT  = 100.0f;
const float BUTTON_SPACING = 8.0f;
const float BUTTON_SPACE_BUFFE = 30.0f;

class button
{
private:
	SDL_FRect srect = { BUTTON_SPACING, BUTTON_SPACING, 480 - 2 * BUTTON_SPACING, BUTTON_HEIGHT };
public:
	inline float getX() const {
		return srect.x;
	}
	inline float getY() const {
		return srect.y;
	}
	inline void incrementY(const float& y) {
		srect.y += y;
	}
	void update(const float& width);
	inline void update(const float& x, const float& y, const float& w, const float& h) {
		srect.x = x; srect.y = y; srect.w = w; srect.h = h;
	}
	inline void update(const float& x, const float& y) {
		srect.x = x; srect.y = y;
	}
	inline void incrementX(const float& x) {
		srect.x += x;
	}
	inline bool hasIntersection(const SDL_FRect* mouse) const {
		return SDL_HasRectIntersectionFloat(&srect, mouse);
	}
	void getDrawData(std::vector<SDL_FRect>& rectData) const;
	//void onHover();
	void (*onClick)(void) = nullptr;
	button() {}
	~button() {}
};	