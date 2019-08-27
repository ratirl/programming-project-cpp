#include "Voertuig.h"

int Voertuig::getId()
{
	return id;
}

std::string Voertuig::getNaam()
{
	return naam;
}

std::string Voertuig::getStatus()
{
	return status;
}

double Voertuig::getTotaalCapaciteit()
{
	return totaalCapaciteit;
}

double Voertuig::getBeschikbaarCapaciteit()
{
	return beschikbaarCapaciteit;
}

void Voertuig::verminderBeschikbaarCapaciteit(double waarde)
{
	this->beschikbaarCapaciteit -= waarde;
}

Voertuig::Voertuig(std::string naam, double totaalCapaciteit)
{
	this->naam = naam;
	this->totaalCapaciteit = totaalCapaciteit;
	this->beschikbaarCapaciteit = totaalCapaciteit;
}

Voertuig::Voertuig(int id, std::string naam, std::string status, double totaalCapaciteit, double beschikbaarCapaciteit, int actief)
{
	this->id = id;
	this->naam = naam;
	this->status = status;
	this->totaalCapaciteit = totaalCapaciteit;
	this->beschikbaarCapaciteit = beschikbaarCapaciteit;
	this->actief = actief;
}
