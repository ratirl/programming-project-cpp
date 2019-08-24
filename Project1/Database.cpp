#include "Database.h"
using namespace mysqlx;

Session Database::getSession()
{
	Session session("172.20.0.200", 33060, "1819IP_groep14", "hosogi");
	return session;
}
