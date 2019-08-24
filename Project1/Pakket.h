#pragma once
#include <iostream>
#include <vector>
#include "string"
using namespace std;

class Pakket {
	//enum Status { magazijn, verwerking, onderweg, geleverd };
private:
	int id;
	string voornaam;
	string achternaam;
	string straat;
	int huisnummer;
	string gemeente;
	string status;
	bool prioriteit;
	double capaciteit;

public:
	int getId();
	string getVoornaam();
	string getAchternaam();
	string getStraat();
	int getHuisnummer();
	string getGemeente();
	string getStatus();
	bool getPrioriteit();

	// constructor met alle members (ga ik wss niet gebruiken)
	Pakket(int id, string voornaam, string achternaam, string straat, int huisnummer, string gemeente, string status, bool prioriteit, double capaciteit);
	Pakket(string voornaam, string achternaam, string straat, int huisnummer, string gemeente, bool prioriteit, double lengte, double breedte);

};