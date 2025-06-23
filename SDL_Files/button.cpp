#include "button.h"
#include <functional>

void button::draw(SDL_Renderer* &renderer) const
{
    SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
    //SDL_RenderRect(renderer, &srect);
    SDL_RenderFillRect(renderer, &srect);
    SDL_SetRenderDrawColor(renderer, 255, 251, 201, 255);
}

button::button(void (*func)(std::string))
{
    onClick = func;
}

void button::update(const float& w) {
    srect.w = w - 2*BUTTON_SPACING;
}