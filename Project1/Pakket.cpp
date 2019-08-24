#include "Pakket.h"

int Pakket::getId()
{
	return id;
}

std::string Pakket::getVoornaam()
{
	return voornaam;
}

std::string Pakket::getAchternaam()
{
	return achternaam;
}

std::string Pakket::getStraat()
{
	return straat;
}

int Pakket::getHuisnummer()
{
	return huisnummer;
}

std::string Pakket::getGemeente()
{
	return gemeente;
}

std::string Pakket::getStatus()
{
	return status;
}

bool Pakket::getPrioriteit()
{
	return prioriteit;
}

Pakket::Pakket(int id, std::string voornaam, std::string achternaam, std::string straat, int huisnummer, std::string gemeente, std::string status, bool prioriteit, double capaciteit)
{
	this->id = id;
	this->voornaam = voornaam;
	this->achternaam = achternaam;
	this->straat = straat;
	this->huisnummer = huisnummer;
	this->gemeente = gemeente;
	this->status = status;
	this->prioriteit = prioriteit;
	this->capaciteit = capaciteit;
}

Pakket::Pakket(std::string voornaam, std::string achternaam, std::string straat, int huisnummer, std::string gemeente, bool prioriteit, double lengte, double breedte)
{
	this->voornaam = voornaam;
	this->achternaam = achternaam;
	this->straat = straat;
	this->huisnummer = huisnummer;
	this->gemeente = gemeente;
	this->status = status;
	this->prioriteit = prioriteit;
	this->capaciteit = lengte * breedte;
}
