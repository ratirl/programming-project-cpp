#include <iostream>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>
#include "Blowfish.h"
#include "Database.h"
#include <vector>
#include <sstream>


using namespace mysqlx;
using namespace std;

class Encryptie {
private:
	Session session = Database::getSession();
	Schema schema = session.getSchema("1819IP_groep14");
	Table tableWerknemer = schema.getTable("L9_Werknemer");
	std::string return_salt();
	std::string hash_vector_to_string(vector<char>);
	std::string char_vector_to_string(vector<char>);
	vector<char> string_to_char_vector(std::string);

	std::string make_hash(std::string, std::string, std::string);

public:
	bool checkLogin(std::string, std::string);
	void make_employee();
	const std::string KEY = "Ali_L9_Solo_Carry";
	std::string EMPLOYEE;
	int safe_cin();
	bool check_pw_choice(std::string);
	std::string check_char(char);
	std::string zwak_pw_loop(std::string);

};