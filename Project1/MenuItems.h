#pragma once
#include <iostream>
#include <string>
//#include "DatabaseHeaders.h"
#include "DatabaseVoertuig.h"
#include "DatabasePakket.h"
using namespace std;
class MenuItems {

public:
	//dit zijn de displays vd menu items, bevatten geen
	//functionaliteit, puur ter weergave vd menu opties
	int hoofdMenu(); //klaar
	int voertuigenInbrengen(); //klaar
	int bestellingenInbrengen();
	int lijstVoertuigLading();
	int voertuigDetails();
	int statistiekenLijsten();
	int pakketDetails();

	//bevatten de logica vd geselecteerde menu optie
	int voertuigMenu();
	int pakketMenu();

};