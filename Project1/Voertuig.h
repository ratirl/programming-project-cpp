#pragma once
#include "Pakket.h"
#include <iostream>

class Voertuig {
private:
	int id;
	std::string naam;
	double totaalCapaciteit;
	double beschikbaarCapaciteit;
	std::vector<Pakket> lading;

public:
	int getId();
	std::string getNaam();
	double getTotaalCapaciteit();
	double getBeschikbaarCapaciteit();
	// zonder id (voor in database te inserten)
	Voertuig(std::string naam, double totaalCapaciteit);
	



};