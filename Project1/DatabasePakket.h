#pragma once
#include "Database.h"
#include "Pakket.h"
using namespace mysqlx;

class DatabasePakket {
public:
	Session session = Database::getSession();
	Schema schema = session.getSchema("1819IP_groep14");
	Table table = schema.getTable("L9_Pakket");

public:
	DatabasePakket();
	//pakket inbrengen in systeem dus opslaan in database
	void addPakket(Pakket p);
	//void archievePakket(int id);

};