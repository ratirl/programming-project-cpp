#include "DatabasePakket.h"



DatabasePakket::DatabasePakket()
{
}

void DatabasePakket::addPakket(Pakket p)
{

	table.insert("userId", "status", "capaciteit", "prioriteit", "voornaam", "achternaam", "straat", "huisnummer", "gemeente").values(
	p.getUserId(), p.getStatus(), p.getCapaciteit(), p.getPrioriteit(), p.getVoornaam(), p.getAchternaam(), p.getStraat(), p.getHuisnummer(), p.getGemeente()).execute();

}
