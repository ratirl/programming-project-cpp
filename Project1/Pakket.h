#pragma once
#include <vector>
#include <iostream>
#include <string>

class Pakket {
	//enum Status { magazijn, verwerking, onderweg, geleverd };
private:
	int id;
	int voertuigId;
	int userId;
	std::string status;
	std::string opmerking;
	double capaciteit;
	int prioriteit;
	std::string voornaam;
	std::string achternaam;
	std::string straat;
	int huisnummer;
	std::string gemeente;
	int actief;

public:
	int getId();
	int getVoertuigId();
	int getUserId();
	std::string getStatus();
	std::string getOpmerking();
	double getCapaciteit();
	int getPrioriteit();
	std::string getVoornaam();
	std::string getAchternaam();
	std::string getStraat();
	int getHuisnummer();
	std::string getGemeente();
	int getActief();
	void setStatus(std::string msg);

	


	// constructor met alle members (ga ik wss niet gebruiken)
	Pakket(int id, int voertuigId, int userId, std::string status, std::string opmerking, double capaciteit, int prioriteit, std::string voornaam, std::string achternaam, std::string straat, int huisnummer, std::string gemeente, int actief);

	//constructor om data in de database op te slaan
	Pakket(int userId, std::string voornaam, std::string achternaam, std::string straat, int huisnummer, std::string gemeente, int prioriteit, double lengte, double breedte);

};