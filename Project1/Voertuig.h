#pragma once
#include "Pakket.h"
#include <iostream>
#include <vector>
#include "string"
using namespace std;

class Voertuig {
private:
	int id;
	string naam;
	double totaalCapaciteit;
	double beschikbaarCapaciteit;
	vector<Pakket> lading;

public:
	int getId();
	string getNaam();
	double getTotaalCapaciteit();
	double getBeschikbaarCapaciteit();
	// zonder id (voor in database te inserten)
	Voertuig(string naam, double totaalCapaciteit);
	



};