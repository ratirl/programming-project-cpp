#include "Pakket.h"

int Pakket::getId()
{
	return id;
}

string Pakket::getVoornaam()
{
	return voornaam;
}

string Pakket::getAchternaam()
{
	return achternaam;
}

string Pakket::getStraat()
{
	return straat;
}

int Pakket::getHuisnummer()
{
	return huisnummer;
}

string Pakket::getGemeente()
{
	return gemeente;
}

string Pakket::getStatus()
{
	return status;
}

bool Pakket::getPrioriteit()
{
	return prioriteit;
}

Pakket::Pakket(int id, string voornaam, string achternaam, string straat, int huisnummer, string gemeente, string status, bool prioriteit, double capaciteit)
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

Pakket::Pakket(string voornaam, string achternaam, string straat, int huisnummer, string gemeente, bool prioriteit, double lengte, double breedte)
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
