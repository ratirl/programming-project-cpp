#include <mysqlx/xdevapi.h>

class Database {
public:
	static mysqlx::Session getSession();
};