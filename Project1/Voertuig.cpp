#include "Voertuig.h"

int Voertuig::getId()
{
	return id;
}

std::string Voertuig::getNaam()
{
	return naam;
}

double Voertuig::getTotaalCapaciteit()
{
	return totaalCapaciteit;
}

double Voertuig::getBeschikbaarCapaciteit()
{
	return beschikbaarCapaciteit;
}

Voertuig::Voertuig(std::string naam, double totaalCapaciteit)
{
	this->naam = naam;
	this->totaalCapaciteit = totaalCapaciteit;
	this->beschikbaarCapaciteit = totaalCapaciteit;
}
