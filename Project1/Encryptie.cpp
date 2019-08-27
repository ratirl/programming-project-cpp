#include "Encryptie.h"

bool Encryptie::checkLogin(std::string user, std::string pass) {

	mysqlx::RowResult myResult = tableWerknemer.select("id", "user", "salt", "hash").where("user= :param").bind("param", user).execute();
	std::string db_user;
	std::string db_salt;
	std::string db_hash;

	for (mysqlx::Row row : myResult.fetchAll()) {
		db_user = row[1];
		db_salt = row[2];
		db_hash = row[3];
		if (user == db_user && db_hash == make_hash(pass, db_salt, KEY)) {
			cout << endl << "    " << "Welkom! Je bent ingelogt als " << row[1] << "." << endl << endl;
			EMPLOYEE = row[1];
			return true;
		}
	}
	return false;
};



std::string Encryptie::return_salt() {
	// https://docs.microsoft.com/en-us/windows/desktop/api/wincrypt/nf-wincrypt-cryptgenrandom
	HCRYPTPROV   hCryptProv;
	BYTE         pbData[16];
	CryptAcquireContext(
		&hCryptProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT);

	CryptGenRandom(
		hCryptProv,
		16,
		pbData);
	// codesnippet van https://stackoverflow.com/questions/22556661/converting-byte-array-containing-non-ascii-characters-to-a-string
	// wist niet precies hoe ik een array van bytes in string kon omzetten voor database (varchar)
	std::string string_data;
	for (int i = 0; i < sizeof(pbData) / sizeof(pbData[0]); i++) {
		char buff[4];
		sprintf(buff, "%02x", (unsigned char)pbData[i]);
		string_data += buff;
	}
	return string_data;
}

void ask_user_and_pw(std::string &a, std::string &b) {
	cout << "    Geef de username in: ";
	getline(cin, a);
	cout << "    Geef de password in: ";
	getline(cin, b);
}
void Encryptie::make_employee() {
	// vragen naar user en pass
	std::string user, pass, confirmation;
	vector<char> wachtwoord;
	cout << "    (opmerking: de password moet minimum 12 characters lang zijn en minstens 2 letters en 2 symbolen bevatten.)" << endl << endl;
	cout << "    Geef de username in: ";
	cin.ignore();
	getline(cin, user);
	cout << "    Geef de password in: ";
	getline(cin, pass);
	pass = zwak_pw_loop(pass);
	cout << "    Geef de password opnieuw in om te confirmen:";
	getline(cin, confirmation);
	while (!pass._Equal(confirmation)) {
		cout << "    Passwoorden komen niet overeen! Probeer aub opnieuw." << endl;
		cout << "    Geef de username in:";
		getline(cin, user);
		cout << "    Geef de password in:";
		getline(cin, pass);
		zwak_pw_loop(pass);
		cout << "    Geef de password opnieuw in om te confirmen:";
		getline(cin, confirmation);
	};
	wachtwoord = string_to_char_vector(pass);

	// opvragen van random salt 
	std::string salt = return_salt();
	std::string temp = salt;

	// altijd dezelfde key
	const vector<char> key = string_to_char_vector("Ali_L9_Solo_Carry");

	// bcrypt (blowfish) object aanmaken mbv de key
	Blowfish bj = Blowfish(key);

	// salt toevoegen aan wachtwoord (ik append de salt vanvoor ipv vanachter voor moest iemand het willen hacken
	// dmv bruteforce dan moeten ze eerste langs de salt ipv langs de wachtwoord (meer resursieve brute force calls)
	std::string salted_pw = temp.append(char_vector_to_string(wachtwoord));

	// hashen met bcrypt
	vector<char> hash_vector = bj.Encrypt(string_to_char_vector(salted_pw));
	std::string hash = hash_vector_to_string(hash_vector);

	// salt en hash opslaan in database
	tableWerknemer.insert("user", "salt", "hash").values(user, salt, hash).execute();
	cout << "    " << "User " << user << " werd aangemaakt!" << endl;
}

vector<char> Encryptie::string_to_char_vector(std::string msg) {
	vector<char> updated_msg(msg.begin(), msg.end());
	return updated_msg;
}

std::string Encryptie::hash_vector_to_string(vector<char> msg) {
	std::string string_data;
	for (int i = 0; i < msg.size(); i++) {
		char buff[4];
		sprintf(buff, "%02x", (unsigned char)msg[i]);
		string_data += buff;
	}
	return string_data;
}

std::string Encryptie::char_vector_to_string(vector<char> msg) {
	std::string updated_msg(msg.begin(), msg.end());
	return updated_msg;
}


std::string Encryptie::make_hash(std::string p, std::string s, std::string k) {
	const vector<char> key = string_to_char_vector(k);
	vector<char> wachtwoord = string_to_char_vector(p);
	Blowfish kappa = Blowfish(key);
	std::string salted_pw = s.append(char_vector_to_string(wachtwoord));
	vector<char> hash_vector = kappa.Encrypt(string_to_char_vector(salted_pw));
	std::string hash = hash_vector_to_string(hash_vector);
	return hash;
}


// If you have special security needs, enforce a minimum length of 12 characters and require
// at least two letters, two digits, and two symbols. https://www.codeproject.com/Articles/704865/Salted-Password-Hashing-Doing-it-Right
bool Encryptie::check_pw_choice(std::string pw) {

	const int lengte = 12;
	const int lengte2 = 2;

	vector<char> input = string_to_char_vector(pw);

	int min_2_letters = 0;
	int min_2_digits = 0;
	int min_2_symbols = 0;

	for (int i = 0; i < input.size(); i++) {
		if (check_char(input[i])._Equal("getal")) {
			min_2_digits++;
		}
		else if (check_char(input[i])._Equal("letter")) {
			min_2_letters++;
		}
		else if (check_char(input[i])._Equal("symbool")) {
			min_2_symbols++;
		}
	}
	if (pw.length() > 11 && min_2_letters > 1 && min_2_digits > 1 && min_2_symbols > 1) {

		return true;
	}
	else return false;
}

int Encryptie::safe_cin() {
	int keuze;
	std::string data;
	while (getline(cin, data))
	{
		std::stringstream ss(data);
		if (ss >> keuze) {
			if (ss.eof()) {
				return keuze;
			}
		}
		cout << "    Type aub een getal in: ";
	}
	return keuze;
}

std::string Encryptie::check_char(char x) {
	int data = int(x);
	if (data > 47 && data < 58) {
		return "getal";
	}
	else if ((data > 64 && data < 91) || (data > 96 && data < 123)) {
		return "letter";
	}
	else return "symbool";
}

std::string Encryptie::zwak_pw_loop(std::string pass) {
	std::string pw = pass;
	while (!check_pw_choice(pw)) {
		cout << "    Zwakke password, kies een andere password. " << endl;
		cout << "    Geef de password in: ";
		getline(cin, pw);
	}
	return pw;
}
