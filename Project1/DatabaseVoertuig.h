#pragma once
#include "Database.h"
#include "Voertuig.h"
using namespace mysqlx;

class DatabaseVoertuig {
private:
	Session session = Database::getSession();
	Schema schema = session.getSchema("1819IP_groep14");
	Table table = schema.getTable("L9_Voertuig");

public:
	DatabaseVoertuig();
	//voertuig toevoegen aan database::basic
	void addVoertuig(std::string naam, double totaalCapaciteit);

};