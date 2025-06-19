#include "database.h"
#include "sqliteStatements.h"

bool database::checkTyping(const databaseTables& table, const databaseColumns& col)
{
	switch (table) {
	case CATEGORYTABLE:
		if (col <= C_COLORINT) {
			return true;
		}
		break;
	case TAGTABLE:
		if (col >= T_NAMETEXT && col <= T_COLORINT) {
			return true;
		}
		break;
	case STATUSTABLE:
		if (col >= S_NAMETEXT && col <= S_CATIDINT) {
			return true;
		}
		break;
	case EVENTTABLE:
		if (col >= E_NAMETEXT && col <= E_NOTETEXT) {
			return true;
		}
		break;
	case EVENTTAGTABLE:
		if (col >= ET_EVIDINT && col <= ET_TAGIDINT) {
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

bool database::checkDataTyping(const databaseColumns& col, databaseDataTypes data)
{
	if (col == C_COLORINT || col == T_COLORINT || col == S_COLORINT || col == S_SORTINT || 
		col == E_PRIOINT || col == E_URGINT || col == E_TESTINT || col == E_STIMEINT || 
		col == E_ENDTIMEINT || col == E_COMPINT || col == E_REMBOOL || col == E_REMINT || 
		col == E_PINBOOL || col == E_SIDINT || col == E_CATIDINT || col == E_UPDATEINT || 
		col == E_PERCOMPINT || col == ET_EVIDINT || col == ET_TAGIDINT || col == S_CATIDINT) {
		if (data == DBINTEGER) {
			return true;
		}
	}
	else {
		if (data == DBSTRING) {
			return true;
		}
	}
	return false;
}

const std::string database::getColumnName(const databaseColumns& col)
{
	switch (col) {
	case C_NAMETEXT:
		return "name";
			break;
	case C_COLORINT:
		return "color";
		break;
	case T_NAMETEXT:
		return "name";
		break;
	case T_COLORINT:
		return "color";
		break;
	case S_NAMETEXT:
		return "name";
		break;
	case S_COLORINT:
		return "color";
		break;
	case S_SORTINT:
		return "sortOrder";
		break;
	case S_CATIDINT:
		return "categoryId";
		break;
	case E_NAMETEXT:
		return "name";
		break;
	case E_DESCTEXT:
		return "description";
		break;
	case E_PRIOINT:
		return "priority";
		break;
	case E_URGINT:
		return "urgency";
		break;
	case E_TESTINT:
		return "timeEstimate";
		break;
	case E_STIMEINT:
		return "startTime";
		break;
	case E_ENDTIMEINT:
		return "endTime";
		break;
	case E_COMPINT:
		return "completedAt";
		break;
	case E_REMBOOL:
		return "reminder";
		break;
	case E_REMINT:
		return "reminderMinutes";
		break;
	case E_PINBOOL:
		return "pinned";
		break;
	case E_SIDINT:
		return "statusId";
		break;
	case E_CATIDINT:
		return "categoryId";
		break;
	case E_RECTEXT:
		return "recurrence";
		break;
	case E_UPDATEINT:
		return "updatedAt";
		break;
	case E_PERCOMPINT:
		return "percentComplete";
		break;
	case E_NOTETEXT:
		return "notes";
		break;
	case ET_EVIDINT:
		return "eventId";
		break;
	case ET_TAGIDINT:
		return "tagId";
		break;
	}
	std::cout << "getColName failed " << col << '\n';
	std::cin.ignore(); std::cin.get();
	return "";
}

const std::string database::getTableName(const databaseTables& table)
{
	switch (table) {
	case CATEGORYTABLE:
		return "categoryTable";
		break;
	case TAGTABLE:
		return "tagTable";
		break;
	case STATUSTABLE:
		return "statusTable";
		break;
	case EVENTTABLE:
		return "eventTable";
		break;
	case EVENTTAGTABLE:
		return "eventtagTable";
		break;
	}
	std::cout << "getTableName failed " << table << '\n';
	std::cin.ignore(); std::cin.get();
	return "";
}

const std::string database::getIdName(const databaseTables& table) {

	if (table == EVENTTAGTABLE) {
		std::cout << "attempting to get an id that doesn't exist \n";
		std::cin.ignore(); std::cin.get();
	}
	switch (table) {
	case CATEGORYTABLE:
		return "categoryId";
		break;
	case TAGTABLE:
		return "tagId";
		break;
	case STATUSTABLE:
		return "statusId";
		break;
	case EVENTTABLE:
		return "eventId";
		break;
	}
	std::cout << "getIdName failed " << table << '\n';
	std::cin.ignore(); std::cin.get();
	return "";
}

database::database(std::string path)
{
	rc = sqlite3_open(path.c_str(), &sqliteDB);
	if (rc == SQLITE_OK) {
		rc = sqlite3_exec(sqliteDB, createTables.c_str(), nullptr, nullptr, &errorMessage);
		if (rc != SQLITE_OK) {
			std::cout << "failed to create tables\n";
			std::cin.ignore(); std::cin.get();
		}
	}
	else {
		std::cout << "failed to connect to data base tables\n";
		std::cin.ignore(); std::cin.get();
	}
}

void database::update_database(const databaseTables& table, const databaseColumns& colName, const std::string& newValue, const int& id)
{
	if (checkTyping(table, colName)) {
		if (checkDataTyping(colName, DBSTRING)) {
			std::string str = "update " + getTableName(table) + "\n" +
				"set " + getColumnName(colName) + " = ?\n"
				"where " + getIdName(table) + " = ? ;";
			sqlite3_prepare_v2(sqliteDB, str.c_str(), -1, &stmt, nullptr);
			sqlite3_bind_text(stmt, 1, newValue.c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_int(stmt, 2, id);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}
		std::cout << "typing error string function called not integer " << table << " " << colName << "\n";
		std::cin.ignore(); std::cin.get();
	}
	else {
		std::cout << "typing error " << table << " " << colName << "\n";
		std::cin.ignore(); std::cin.get();
	}

}

void database::update_database(const databaseTables& table, const databaseColumns& colName, const int& newValue, const int& id)
{
	if (colName == ET_EVIDINT || colName == ET_TAGIDINT) {
		std::cout << "trying to modify unmodifiable ids \n";
		std::cin.ignore(); std::cin.get();
	}
	if (checkTyping(table, colName)) {
		if (checkDataTyping(colName, DBINTEGER)) {
			std::string str = "update " + getTableName(table) + "\n" +
				"set " + getColumnName(colName) + " = ?\n"
				"where " + getIdName(table) + " = ? ;";
			sqlite3_prepare_v2(sqliteDB, str.c_str(), -1, &stmt, nullptr);
			sqlite3_bind_int(stmt, 1, newValue);
			sqlite3_bind_int(stmt, 2, id);
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
		}
		std::cout << "typing error integer function called not string " << table << " " << colName << "\n";
		std::cin.ignore(); std::cin.get();
	}
	else {
		std::cout << "typing error " << table << " " << colName << "\n";
		std::cin.ignore(); std::cin.get();
	}
}

void database::insert_tag(const tagTable& tagEntry)
{
	std::string str = "insert into tagTable (name, color)\nvalues ( ? , ? );";
	sqlite3_prepare_v2(sqliteDB, str.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, tagEntry.name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, tagEntry.color);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void database::insert_cat(const categoryTable& catEntry)
{
	std::string str = "insert into categoryTable (name, color)\nvalues ( ? , ? );";
	sqlite3_prepare_v2(sqliteDB, str.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, catEntry.name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, catEntry.color);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void database::insert_status(const statusTable& statusEntry)
{
	std::string str = "insert into statusTable (name, color, sortOrder, categoryId)\nvalues ( ? , ? , ? , ? );";
	sqlite3_prepare_v2(sqliteDB, str.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, statusEntry.name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, statusEntry.color);
	sqlite3_bind_int(stmt, 3, statusEntry.sortOrder);
	sqlite3_bind_int(stmt, 4, statusEntry.categoryId);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void database::insert_event(const eventTable& eventEntry)
{
	std::time_t currTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string str = "insert into eventTable (name, description, priority, urgency, timeEstimate, startTime, endTime, completedAt, reminder, reminderMinutes, pinned, statusId, categoryId, recurrence, createdAt, updatedAt, percentComplete, notes)\nvalues( ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? );";
	sqlite3_prepare_v2(sqliteDB, str.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, eventEntry.name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, eventEntry.description.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, eventEntry.priority);
	sqlite3_bind_int(stmt, 4, eventEntry.urgency);
	sqlite3_bind_int(stmt, 5, eventEntry.timeEstimate);
	sqlite3_bind_int64(stmt, 6, eventEntry.startTime);
	sqlite3_bind_int64(stmt, 7, eventEntry.endTime);
	sqlite3_bind_int64(stmt, 8, eventEntry.completedAt);
	sqlite3_bind_int(stmt, 9, eventEntry.reminder);
	sqlite3_bind_int(stmt, 10, eventEntry.reminderMinutes);
	sqlite3_bind_int(stmt, 11, eventEntry.pinned);
	sqlite3_bind_int(stmt, 12, eventEntry.statusId);
	sqlite3_bind_int(stmt, 13, eventEntry.categoryId);
	sqlite3_bind_text(stmt, 14, eventEntry.recurrence.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 15, currTime);
	sqlite3_bind_int64(stmt, 16, currTime);
	sqlite3_bind_int(stmt, 17, eventEntry.percentComplete);
	sqlite3_bind_text(stmt, 18, eventEntry.notes.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void database::insert_eventTag(int eventId, int tagId)
{
	std::string str = "insert into eventtagTable (eventId, tagId)\nvalues(" + std::to_string(eventId) + ", " + std::to_string(tagId) + ");";
	sqlite3_exec(sqliteDB, str.c_str(), nullptr, nullptr, &errorMessage);
	if (errorMessage) {
		std::cout << "errmsg: " << errorMessage << '\n';
		std::cin.ignore(); std::cin.get();
	}
}

void database::remove_entry(const int& eventid, const int& tagid)
{
	std::string str = "delete from eventtagTable\nwhere  eventId = " + std::to_string(eventid) + " and tagId = " + std::to_string(tagid) + ";";
	sqlite3_exec(sqliteDB, str.c_str(), nullptr, nullptr, &errorMessage);
	if (errorMessage) {
		std::cout << "errmsg: " << errorMessage << '\n';
		std::cin.ignore(); std::cin.get();
	}
}

void database::remove_entry(const databaseTables& table, const int& id)
{
	std::string str = "delete from " + getTableName(table) + "\nwhere " + getIdName(table) + " = " + std::to_string(id) + ";";
	sqlite3_exec(sqliteDB, str.c_str(), nullptr, nullptr, &errorMessage);
	if (errorMessage) {
		std::cout << "errmsg: " << errorMessage << '\n';
		std::cin.ignore(); std::cin.get();
	}
}

void database::fetch_data()
{
	eventTable eT;
	statusTable sT;
	tagTable tT;
	categoryTable cT;
	std::unordered_map<int, std::vector<int>> eventTag;
	std::unordered_map<int, int> tagmp;
	std::unordered_map<int, int> catmp;
	std::unordered_map<int, int> stamp;

	rc = sqlite3_prepare_v2(sqliteDB, "SELECT * from categoryTable;", -1, &stmt, nullptr);
	int counter = 0;
	if (rc != SQLITE_OK) {
		std::cout << "failed fetching data 2\n";
		std::cin.ignore(); std::cin.get();
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		cT.categoryId = sqlite3_column_int(stmt, 0);
		const unsigned char* cptr1 = sqlite3_column_text(stmt, 1);
		if (cptr1) {
			cT.name = reinterpret_cast<const char*>(cptr1);
		}
		cT.color = sqlite3_column_int(stmt, 2);
		catmp[cT.categoryId] = counter;
		categoryVector.push_back(cT);
		counter++;
	}
	sqlite3_finalize(stmt);

	counter = 0;
	rc = sqlite3_prepare_v2(sqliteDB, "SELECT * from tagTable;", -1, &stmt, nullptr);

	if (rc != SQLITE_OK) {
		std::cout << "failed fetching data 3\n";
		std::cin.ignore(); std::cin.get();
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		tT.tagId = sqlite3_column_int(stmt, 0);
		const unsigned char* cptr2 = sqlite3_column_text(stmt, 1);
		if (cptr2) {
			tT.name = reinterpret_cast<const char*>(cptr2);
		}
		tT.color = sqlite3_column_int(stmt, 2);
		tagmp[tT.tagId] = counter;
		tagVector.push_back(tT);
		counter++;
	}
	sqlite3_finalize(stmt);

	counter = 0;
	rc = sqlite3_prepare_v2(sqliteDB, "SELECT * from statusTable;", -1, &stmt, nullptr);

	if (rc != SQLITE_OK) {
		std::cout << "failed fetching data 4\n";
		std::cin.ignore(); std::cin.get();
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		sT.statusId = sqlite3_column_int(stmt, 0);
		const unsigned char* cptr3 = sqlite3_column_text(stmt, 1);
		if (cptr3) {
			sT.name = reinterpret_cast<const char*>(cptr3);
		}
		sT.color = sqlite3_column_int(stmt, 2);
		sT.sortOrder = sqlite3_column_int(stmt, 3);
		sT.categoryId = sqlite3_column_int(stmt, 4);
		stamp[sT.statusId] = counter;
		statusVector.push_back(sT);
		counter++;
	}
	sqlite3_finalize(stmt);

	rc = sqlite3_prepare_v2(sqliteDB, "SELECT * from eventtagTable;", -1, &stmt, nullptr);

	if (rc != SQLITE_OK) {
		std::cout << "failed fetching data 5\n";
		std::cin.ignore(); std::cin.get();
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		eventTag[sqlite3_column_int(stmt, 0)].push_back(sqlite3_column_int(stmt, 1));
	}

	sqlite3_finalize(stmt);

	rc = sqlite3_prepare_v2(sqliteDB, "SELECT * from eventTable;", -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cout << "failed fetching data 1\n";
		std::cin.ignore(); std::cin.get();
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		eT.eventId = sqlite3_column_int(stmt, 0);
		const unsigned char* cptr4 = sqlite3_column_text(stmt, 1);
		if (cptr4) {
			eT.name = reinterpret_cast<const char*>(cptr4);
		}
		const unsigned char* cptr5 = sqlite3_column_text(stmt, 2);
		if (cptr5) {
			eT.description = reinterpret_cast<const char*>(cptr5);
		}
		eT.priority = sqlite3_column_int(stmt, 3);
		eT.urgency = sqlite3_column_int(stmt, 4);
		eT.timeEstimate = sqlite3_column_int(stmt, 5);
		eT.startTime = sqlite3_column_int64(stmt, 6);
		eT.endTime = sqlite3_column_int64(stmt, 7);
		eT.completedAt = sqlite3_column_int(stmt, 8);
		eT.reminder = (sqlite3_column_int(stmt, 9) != 0);
		eT.reminderMinutes = sqlite3_column_int(stmt, 10);
		eT.pinned = (sqlite3_column_int(stmt, 11) != 0);
		eT.statusId = sqlite3_column_int(stmt, 12);
		eT.categoryId = sqlite3_column_int(stmt, 13);
		const unsigned char* cptr6 = sqlite3_column_text(stmt, 14);
		if (cptr6) {
			eT.recurrence = reinterpret_cast<const char*>(cptr6);
		}
		eT.createdAt = sqlite3_column_int64(stmt, 15);
		eT.updatedAt = sqlite3_column_int64(stmt, 16);
		eT.percentComplete = sqlite3_column_int(stmt, 17);
		const unsigned char* cptr7 = sqlite3_column_text(stmt, 18);
		if (cptr7) {
			eT.notes = reinterpret_cast<const char*>(cptr7);
		}
		if (eT.categoryId) {
			eT.categoryIndex = catmp[eT.categoryId];
		}
		if (eT.statusId) {
			eT.statusIndex = stamp[eT.statusId];
		}
		size_t vecSize = eventTag[eT.categoryId].size();
		for (size_t i = 0; i < vecSize; i++) {
			eT.tagIndex.push_back(tagmp[eventTag[eT.categoryId][i]]);
		}
		eventVector.push_back(eT);
	}

	sqlite3_finalize(stmt);

	return;
}

database::~database()
{
	if (errorMessage) {
		sqlite3_free(errorMessage);
	}
	sqlite3_close(sqliteDB);
}

