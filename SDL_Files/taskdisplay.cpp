#include "taskdisplay.h"

void print(std::string str) {
	std::cout << str << '\n';
}

void taskdisplay::draw(SDL_Renderer*& renderer, TTF_Font*& font1, TTF_Font*& font2)
{
	for (int i = 0; i < tasks.size(); i++) {
		tasks[i].draw(renderer, font1, font2);
	}
}

void taskdisplay::fetchDataBase()
{
	db.fetch_data(&eventVector, &statusVector, &tagVector, &categoryVector);
	for (int i = 0; i < eventVector.size(); i++) {
		taskunit task(print, i, 480, eventVector[i]);
		tasks.push_back(task);
	}

	return;
}

void taskdisplay::checkClick(SDL_FRect* mouse)
{
	for (int i = 0; i < tasks.size(); i++) {
		if (tasks[i].hasIntersection(mouse)) {
			tasks[i].clicked();
			return;
		}
	}
}

void taskdisplay::incrementY(const float& y) {
	for (int i = 0; i < tasks.size(); i++) {
		tasks[i].incrementY(y);
	}
}
