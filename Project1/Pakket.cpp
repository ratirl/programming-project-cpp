#include "Pakket.h"

int Pakket::getId()
{
	return id;
}

int Pakket::getVoertuigId()
{
	return voertuigId;
}

int Pakket::getUserId()
{
	return userId;
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

int Pakket::getActief()
{
	return actief;
}

std::string Pakket::getStatus()
{
	return status;
}

std::string Pakket::getOpmerking()
{
	return opmerking;
}

double Pakket::getCapaciteit()
{
	return capaciteit;
}

int Pakket::getPrioriteit()
{
	return prioriteit;
}

Pakket::Pakket(int id, int voertuigId, int userId, std::string status, std::string opmerking, double capaciteit, int prioriteit, std::string voornaam, std::string achternaam, std::string straat, int huisnummer, std::string gemeente, int actief)
{
	this->id = id;
	this->voertuigId = voertuigId;
	this->userId = userId;
	this->status = status;
	this->opmerking = opmerking;
	this->capaciteit = capaciteit;
	this->prioriteit = prioriteit;
	this->voornaam = voornaam;
	this->achternaam = achternaam;
	this->straat = straat;
	this->huisnummer = huisnummer;
	this->gemeente = gemeente;
	this->actief = actief;
}

Pakket::Pakket(int userId, std::string voornaam, std::string achternaam, std::string straat, int huisnummer, std::string gemeente, int prioriteit, double lengte, double breedte)
{
	this->userId = userId;
	this->voornaam = voornaam;
	this->achternaam = achternaam;
	this->straat = straat;
	this->huisnummer = huisnummer;
	this->gemeente = gemeente;
	this->status = status;
	this->prioriteit = prioriteit;
	this->capaciteit = lengte * breedte;
}
