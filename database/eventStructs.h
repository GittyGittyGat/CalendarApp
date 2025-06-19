#pragma once
#include <string>
#include <chrono>
#include <vector>

struct statusTable {
	int statusId = 0;
	std::string name;
	int color = 0;
	int sortOrder = 0 ;
	int categoryId = 0;
};

struct tagTable {
	int tagId = 0;
	std::string name;
	int color = 0;
};

struct categoryTable {
	int categoryId = 0;
	std::string name;
	int color = 0;
};

struct eventTable {
	int eventId = 0;
	std::string name;
	std::string description;
	int priority = 0;
	int urgency = 0;
	/*
	* cool idea: bit packing time such that 5 bits are used for day, 4 bits for month and 22 (if signed) for year
	* cons: takes longer to develop time so I will avoid it.
	*/
	int timeEstimate = 0;
	std::time_t startTime = 0;
	std::time_t endTime = 0;
	std::time_t completedAt = 0;
	bool reminder = 0;
	int reminderMinutes = 0;
	int pinned = 0;
	int statusId = 0;
	int statusIndex = 0;
	std::string recurrence;
	int categoryId = 0; // index in category vector
	int categoryIndex = 0;
	std::vector<int> tagIndex; // vector of indices in tag vector
	std::time_t createdAt = 0;
	std::time_t updatedAt = 0;
	int percentComplete = 0;
	std::string notes;
};
