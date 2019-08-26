#include <iostream>
#include "blowfish.h"
#include "MenuItems.h"

using namespace std;
using namespace mysqlx;

//vector<char> toChar(std::string msg) {
//	vector<char> updated_msg(msg.begin(), msg.end());
//	return updated_msg;
//}
//std::string toString(vector<char> msg) {
	//std::string string_data;
	//for (int i = 0; i < msg.size(); i++) {
//		char buff[4];
	//	sprintf(buff, "%02x", (unsigned char)msg[i]);
	//	string_data += buff;
//	}
//	return string_data;
//}

int main()
{

//	const vector<char> key = { 'A', 'l', 'i','L', '9', 'S','o', 'l', 'o','C', 'a', 'r','r','y' };
//	vector<char> pass = toChar("coolewachtwoord");
//	Blowfish bj = Blowfish(key);
//	std::string hash = toString(bj.Encrypt(pass));

//	Session session = Database::getSession();
//	Schema schema = session.getSchema("1819IP_groep14");
//	Table table = schema.getTable("RATIRL");
//	table.insert("name").values(hash).execute();

	//voertuig toeveogen in database test
	//DatabaseVoertuig db;
	//db.addVoertuig("vrachtwagen", 10);

	//begin menu
	MenuItems menu;
	int keuze;
	do {
		keuze = menu.hoofdMenu();
		switch (keuze) {
		case 1: menu.voertuigMenu();
			break;
		case 2: menu.pakketMenu();
			break;
		case 3: menu.lijstVoertuigLading();
			break;
		case 4: menu.voertuigDetails();
			break;
		case 5: menu.statistiekenLijsten();
			break;
		case 6: menu.pakketDetails();
			break;
		}
	} while (keuze != 0);
	return 0;
}

