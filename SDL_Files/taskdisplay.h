#pragma once
#include "../database/database.h"
#include "taskunit.h"

const int STARTING_WIN_HEIGHT = 720;
const int STARTING_WIN_WIDTH = 480;


class taskdisplay
{
	// for now fixed 7 tasks to display, 2 as a buffer

	/*
	* ratehr than draw each element, this will draw all the elements together
	* must update taskunit -> draw to taskunit -> get elemnts to draw and render them here
	* must use SDL_RenderLines and SDL_RenderFillRects
	*/

private:
	int startRenderIndex = 0;
	int endRenderIndex = 6;
	std::vector<eventTable> eventVector;
	std::vector<statusTable> statusVector;
	std::vector<tagTable> tagVector;
	std::vector<categoryTable> categoryVector;
	std::vector<taskunit> tasks;
	database db;
	int windowWidth = STARTING_WIN_WIDTH, windowHeight = STARTING_WIN_HEIGHT;
	bool dataNeedsUpdate = true;
public:
	void draw(SDL_Renderer*& renderer, TTF_Font*& font1, TTF_Font*& font2, std::vector<SDL_Texture*>& zeroToNine);
	void fetchDataBase();
	void checkSwipe(SDL_FRect* mouse, SDL_FRect* initPosition);
	taskdisplay(std::string databasePath);
	unsigned int checkClick(SDL_FRect* mouse);
	eventTable* getEventTable(unsigned int idx) {
		return tasks[idx].getEventTable();
	}
	void updateWindowSize(const int& width, const int& height) {

	}
	void incrementY(const float& y);

};