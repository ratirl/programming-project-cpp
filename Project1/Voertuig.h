#pragma once
#include "Pakket.h"
#include <iostream>

class Voertuig {
private:
	int id;
	std::string naam;
	std::string status;
	double totaalCapaciteit;
	double beschikbaarCapaciteit;
	std::vector<Pakket> lading;
	int actief;

public:
	int getId();
	std::string getNaam();
	std::string getStatus();
	double getTotaalCapaciteit();
	double getBeschikbaarCapaciteit();
	void verminderBeschikbaarCapaciteit(double waarde);
	// zonder id (voor in database te inserten)
	Voertuig(std::string naam, double totaalCapaciteit);
	
	//met id en alles
	Voertuig(int id, std::string naam, std::string status, double totaalCapaciteit, double beschikbaarCapaciteit, int actief);



};