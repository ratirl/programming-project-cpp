#include <iostream>
#include "Database.h"
using namespace std;
using namespace mysqlx;

int main()
{
	Session session = Database::getSession();
	Schema schema = session.getSchema("1819IP_groep14");
	Table table = schema.getTable("RATIRL");
	table.insert("id", "name").values(1, "testinput").execute();
	cout << "Test om te zien of github werkt";
	return 0;
}