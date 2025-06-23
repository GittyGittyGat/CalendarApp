#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <functional>

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
	void update(const float& x, const float& y) {
		srect.x = x; srect.y = y;
	}
	inline bool hasIntersection(const SDL_FRect* mouse) const {
		return SDL_HasRectIntersectionFloat(&srect, mouse);
	}
	void draw(SDL_Renderer* &renderer) const;
	//void onHover();
	void (*onClick)(std::string);
	button(void (*func)(std::string));
	~button() {}
};	