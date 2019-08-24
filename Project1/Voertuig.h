#pragma once
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
	Voertuig(string naam, double totaalCapaciteit);

};