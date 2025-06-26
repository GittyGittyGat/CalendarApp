#include "button.h"
#include <functional>

void button::getDrawData(std::vector<SDL_FRect>& rectData) const
{
    rectData.push_back(srect);
    //SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
    //SDL_RenderRect(renderer, &srect);
    //SDL_RenderFillRect(renderer, &srect);
    //SDL_SetRenderDrawColor(renderer, 255, 251, 201, 255);
}

void button::update(const float& w) {
    srect.w = w - 2*BUTTON_SPACING;
}