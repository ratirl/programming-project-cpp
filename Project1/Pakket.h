#pragma once
#include <vector>
#include <iostream>
#include <string>

class Pakket {
	//enum Status { magazijn, verwerking, onderweg, geleverd };
private:
	int id;
	std::string voornaam;
	std::string achternaam;
	std::string straat;
	int huisnummer;
	std::string gemeente;
	std::string status;
	bool prioriteit;
	double capaciteit;

public:
	int getId();
	std::string getVoornaam();
	std::string getAchternaam();
	std::string getStraat();
	int getHuisnummer();
	std::string getGemeente();
	std::string getStatus();
	bool getPrioriteit();

	// constructor met alle members (ga ik wss niet gebruiken)
	Pakket(int id, std::string voornaam, std::string achternaam, std::string straat, int huisnummer, std::string gemeente, std::string status, bool prioriteit, double capaciteit);
	Pakket(std::string voornaam, std::string achternaam, std::string straat, int huisnummer, std::string gemeente, bool prioriteit, double lengte, double breedte);

};