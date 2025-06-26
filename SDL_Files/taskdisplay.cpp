#include "taskdisplay.h"

static void print(std::string str) {
	std::cout << str << '\n';
}

//SDL_Color tasksColor = { 128, 0, 0, 255 };
//SDL_Color urgCircleColor = { 0, 255, 255, 255 };
//SDL_Color PrioCircleColor = { 255, 255, 0, 255 };
//SDL_Color backGroundColor = { 255, 251, 201, 255 };

SDL_Color tasksColor = { 0x00, 0x3B, 0x46, 255 };
SDL_Color urgCircleColor = { 0xFF, 0x8C, 0x94, 255 };
SDL_Color PrioCircleColor = { 0xEC, 0x20, 0x49, 255 };
SDL_Color backGroundColor = { 0x23, 0x23, 0x23, 255 };



void taskdisplay::draw(SDL_Renderer*& renderer, TTF_Font*& font1, TTF_Font*& font2, std::vector<SDL_Texture*>& zeroToNine)
{
	static std::vector<SDL_FRect> rectData;
	static std::vector<std::vector<SDL_FPoint>> circsData; // even is urg, odd is prio
	if (dataNeedsUpdate) {
		rectData.clear();
		circsData.clear();
		for (int i = 0; i < tasks.size(); i++) {
			tasks[i].getDrawData(circsData, rectData);
		}
		dataNeedsUpdate = false;
	}
	SDL_SetRenderDrawColor(renderer, tasksColor.r, tasksColor.g, tasksColor.b, tasksColor.a);
	SDL_RenderFillRects(renderer, rectData.data(), (int)rectData.size());

	SDL_SetRenderDrawColor(renderer, urgCircleColor.r, urgCircleColor.g, urgCircleColor.b, urgCircleColor.a);
	for (size_t i = 0; i < circsData.size(); i += 2) {
		SDL_RenderLines(renderer, circsData[i].data(), (int)circsData[i].size() - 1);
	}

	SDL_SetRenderDrawColor(renderer, PrioCircleColor.r, PrioCircleColor.g, PrioCircleColor.b, PrioCircleColor.a);
	for (size_t i = 1; i < circsData.size(); i += 2) {
		SDL_RenderLines(renderer, circsData[i].data(), (int)circsData[i].size() - 1);
	}

	for (size_t i = 0; i < tasks.size(); i++) {
		tasks[i].drawText(renderer, font1, font2, zeroToNine);
	}
	
	SDL_SetRenderDrawColor(renderer, backGroundColor.r, backGroundColor.g, backGroundColor.b, backGroundColor.a);
	
}

void taskdisplay::fetchDataBase()
{
	db.fetch_data(&eventVector, &statusVector, &tagVector, &categoryVector);
	for (int i = 0; i < eventVector.size(); i++) {
		taskunit task(i, 480, eventVector[i]);
		tasks.push_back(task);
	}

	return;
}

void taskdisplay::checkSwipe(SDL_FRect* mouse, SDL_FRect* initPosition)
{
	for (int i = 0; i < tasks.size(); i++) {
		if (tasks[i].hasIntersection(mouse)) {
			dataNeedsUpdate = true;
			tasks[i].swipe(mouse, initPosition);
			return;
		}
	}
}

taskdisplay::taskdisplay(std::string databasePath) : db(databasePath) {

}

unsigned int taskdisplay::checkClick(SDL_FRect* mouse)
{
	for (int i = 0; i < tasks.size(); i++) {
		if (tasks[i].hasIntersection(mouse)) {
			return i + 1;
		}
	}
	return false;
}

void taskdisplay::incrementY(const float& y) {
	dataNeedsUpdate = true;
	for (int i = 0; i < tasks.size(); i++) {
		tasks[i].incrementY(y);
	}
}
