#include "DatabaseVoertuig.h"

DatabaseVoertuig::DatabaseVoertuig()
{
}

void DatabaseVoertuig::addVoertuig(std::string naam, double totaalCapaciteit)
{
	table.insert("naam", "totaalCapaciteit").values(naam, totaalCapaciteit).execute();
}

void DatabaseVoertuig::archieveVoertuig(int id)
{
	table.update().set("actief", 0).where("id = :param").bind("param", id).execute();
}