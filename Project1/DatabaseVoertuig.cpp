#include "DatabaseVoertuig.h"

DatabaseVoertuig::DatabaseVoertuig()
{
}

void DatabaseVoertuig::addVoertuig(std::string naam, double totaalCapaciteit)
{
	table.insert("naam", "totaalCapaciteit").values(naam, totaalCapaciteit).execute();
}
