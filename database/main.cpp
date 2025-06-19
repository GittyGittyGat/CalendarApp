#include <iostream>
#include "dataBase.h"
//#include "sqliteStatements.h"

int main() {
	int rc = 0;

	database mydb("dateEvents.db");
	mydb.fetch_data();
	eventTable eT;
	eT.name = "this is a new TASK";
	eT.description = "this is my CURR DESC";
	mydb.insert_event(eT);
	char* errorMessage = nullptr;
	//rc = sqlite3_exec(db, createTables.c_str(), nullptr, nullptr, &errorMessage);

	if (rc != SQLITE_OK) {
		std::cout << "SQL ERROR: " << errorMessage << '\n';
		return -1;
	}

	return 0;

}