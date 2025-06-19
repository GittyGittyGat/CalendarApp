#pragma once
#include <string>

//future to do, add userId for multiuser functionality.

const std::string createTables = "CREATE TABLE IF NOT EXISTS categoryTable(\
	categoryId INTEGER PRIMARY KEY AUTOINCREMENT, \
	name TEXT NOT NULL UNIQUE,\
	color INTEGER\
); \
\
CREATE TABLE IF NOT EXISTS tagTable(\
	tagId INTEGER PRIMARY KEY AUTOINCREMENT,\
	name TEXT NOT NULL UNIQUE,\
	color INTEGER\
);\
\
CREATE TABLE IF NOT EXISTS statusTable(\
	statusId INTEGER PRIMARY KEY AUTOINCREMENT,\
	name TEXT NOT NULL UNIQUE,\
	color INTEGER,\
	sortOrder INTEGER,\
	categoryId INTEGER,\
	FOREIGN KEY(categoryId) REFERENCES categoryTable(categoryId)\
);\
\
CREATE TABLE IF NOT EXISTS eventTable (\
	eventId INTEGER PRIMARY KEY AUTOINCREMENT,\
	name TEXT NOT NULL,\
	description TEXT,\
	priority INTEGER,\
	urgency INTEGER,\
	timeEstimate INTEGER,\
	startTime INTEGER,\
	endTime INTEGER,\
	completedAt INTEGER,\
	reminder BOOLEAN,\
	reminderMinutes INTEGER,\
	pinned BOOLEAN,\
	statusId INTEGER,\
	categoryId INTEGER,\
	recurrence TEXT,\
	createdAt INTEGER,\
	updatedAt INTEGER,\
	percentComplete INTEGER,\
	notes TEXT,\
	FOREIGN KEY(statusId) REFERENCES statusTable(statusId),\
	FOREIGN KEY(categoryId) REFERENCES categoryTable(categoryId)\
);\
\
CREATE TABLE IF NOT EXISTS eventtagTable(\
	eventId INTEGER,\
	tagId INTEGER,\
	FOREIGN KEY (eventId) REFERENCES eventTable(eventId),\
	FOREIGN KEY(tagId) REFERENCES tagTable(tagId)\
	PRIMARY KEY(eventId, tagId)\
);";
