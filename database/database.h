#pragma once
#include "SQLite3/sqlite3.h"
#include "eventStructs.h"
#include <iostream>
#include <unordered_map>

enum databaseTables {CATEGORYTABLE, TAGTABLE, STATUSTABLE, EVENTTABLE, EVENTTAGTABLE};
enum databaseColumns {C_NAMETEXT, C_COLORINT, T_NAMETEXT, T_COLORINT, S_NAMETEXT, S_COLORINT, S_SORTINT, S_CATIDINT, E_NAMETEXT,
	E_DESCTEXT, E_PRIOINT, E_URGINT, E_TESTINT, E_STIMEINT, E_ENDTIMEINT, E_COMPINT, E_REMBOOL, E_REMINT, E_PINBOOL,
	E_SIDINT, E_CATIDINT, E_RECTEXT, E_UPDATEINT, E_PERCOMPINT, E_NOTETEXT, ET_EVIDINT, ET_TAGIDINT
};
enum databaseDataTypes {DBINTEGER, DBSTRING};

class database
{
private:
	char* errorMessage = nullptr; // always check if it's null and delete if not.
	sqlite3* sqliteDB;
	int rc = 0;
	sqlite3_stmt* stmt;
	std::vector<eventTable> eventVector;
	std::vector<statusTable> statusVector;
	std::vector<tagTable> tagVector;
	std::vector<categoryTable> categoryVector;
	bool checkTyping(const databaseTables&, const databaseColumns&);
	bool checkDataTyping(const databaseColumns&, databaseDataTypes);
	const std::string getTableName(const databaseTables&);
	const std::string getColumnName(const databaseColumns&);
	const std::string getIdName(const databaseTables& table);

public:
	database(std::string path);
	void update_database(const databaseTables& table, const databaseColumns& colName, const std::string& newValue, const int& id);
	void update_database(const databaseTables& table, const databaseColumns& colName, const int& newValue,  const int& id);
	//int insert_data(std::string table, std::string colName, const variables& value);
	//not adding delete for now.
	void insert_tag(const tagTable& tagEntry);
	void insert_cat(const categoryTable& catEntry);
	void insert_status(const statusTable& statusEntry);
	void insert_event(const eventTable& eventEntry);
	void insert_eventTag(int eventId, int tagId);
	void remove_entry(const databaseTables& table, const int& id);
	void remove_entry(const int& catid, const int& tagid);
	void fetch_data();
	~database();
};
