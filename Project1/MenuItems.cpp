#include "MenuItems.h"


//database objecten
DatabaseVoertuig VOERTUIG;
DatabasePakket PAKKET;

int MenuItems::hoofdMenu()
{
	int keuze;
	do {
		cout << "    | hoofdmenu |    " << endl << endl;
		cout << "    1. voertuigen inbrengen" << endl;
		cout << "    2. bestellingen inbrengen" << endl;
		cout << "    3. lijst voertuig met lading" << endl;
		cout << "    4. detals voertuig" << endl;
		cout << "    5. statistieken lijsten" << endl;
		cout << "    6. detals pakket" << endl;
		cout << "    0. sluiten" << endl << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;

		if ((keuze < 0) || (keuze > 6)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while (((keuze < 0) || (keuze > 6)));
	return keuze;
}

int MenuItems::voertuigenInbrengen() {

	int keuze;
	do {
		cout << "    1. voertuig inbrengen" << endl;//voertuig moet ook een status hebben
		cout << "    2. voertuig archiveren" << endl; //actief naar 0 zetten in de database
		cout << "    0. terug" << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;
		if ((keuze < 0) || (keuze > 2)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while ((keuze < 0) || (keuze > 2));
	return keuze;
}

int MenuItems::bestellingenInbrengen() {
	int keuze;
	do {
		cout << "    1. bestelling inbrengen" << endl;
		cout << "    2. archiveren archiveren" << endl; //actief naar 0 zetten in de database
		cout << "    0. terug" << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;
		if ((keuze < 0) || (keuze > 2)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while ((keuze < 0) || (keuze > 2));
	return keuze;
}

int MenuItems::lijstVoertuigLading() {
	int keuze;
	do {
		cout << "    1. vul voertuigen" << endl; //vul enkel de voertuigen die atm status hebben van niet bezet
		cout << "    2. overzicht voertuigen met lading" << endl; //overzicht tonen welke voertuigen met welke paketten gevult moeten worden
		cout << "    0. terug" << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;
		if ((keuze < 0) || (keuze > 2)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while ((keuze < 0) || (keuze > 2));
	return keuze;
}

int MenuItems::voertuigDetails() {
	int keuze;
	do {
		//toont initieel lijst val alle voertuigen met hun bijhorend id, user moet dan id ingeven voor meer details
		cout << "    1. toon status en paketten van voertuig x" << endl; //user geeft id in vd voertuig
		cout << "    2. editeer status van voertuig x" << endl; //update status vd voertuig
		cout << "    3. editeer pakket van voertuig x" << endl; //update pakket details vd voertuig
		cout << "    0. terug" << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;
		if ((keuze < 0) || (keuze > 3)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while ((keuze < 0) || (keuze > 3));
	return keuze;
}

int MenuItems::statistiekenLijsten() {
	int keuze;
	do {
		cout << "    1. opvragen status van paket x" << endl;
		cout << "    2. overzicht leveringen per gemeente" << endl;
		cout << "    0. terug" << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;
		if ((keuze < 0) || (keuze > 2)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while ((keuze < 0) || (keuze > 2));
	return keuze;
}

int MenuItems::pakketDetails() {
	int keuze;
	do {
		cout << "    1. opvragen status van pakket x" << endl;
		cout << "    2. updaten status van pakket x" << endl;
		cout << "    3. editeer pakket van voertuig x" << endl;
		cout << "    0. terug" << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;
		if ((keuze < 0) || (keuze > 3)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while ((keuze < 0) || (keuze > 3));
	return keuze;
}





int MenuItems::voertuigMenu() {
	cout << "    | voertuigmenu |    " << endl << endl;
	int keuze;
	do {
		keuze = MenuItems::voertuigenInbrengen();
		switch (keuze) {
		case 1: {

			std::string name;
			double capaciteit;
			cout << "    geef de naam van de auto in: ";
			cin >> name;
			cout << "    geef de capaciteit in in m2: ";
			cin >> capaciteit;
			cin.ignore();
			VOERTUIG.addVoertuig(name, capaciteit);
		} break;

		case 2: {
			int id;
			cout << "    geef de voertuig id: ";
			cin >> id;
			VOERTUIG.archieveVoertuig(id);
		} break;
		}

	} while (keuze != 0);
	return keuze;
}

int MenuItems::pakketMenu() {
	cout << "    | pakketmenu |    " << endl << endl;
	int keuze;
	do {
		keuze = MenuItems::bestellingenInbrengen();
		switch (keuze) {
		case 1: {
			int userId;
			std::string voornaam;
			std::string achternaam;
			std::string straat;
			int huisnummer;
			std::string gemeente;
			int prioriteit;
			double lengte;
			double breedte;

			cout << "    geef userid: ";
			cin >> userId;
			cout << "    geef voornaam: ";
			cin >> voornaam;
			cout << "    geef achternaam: ";
			cin >> achternaam;
			cout << "    geef straat: ";
			cin >> straat;
			cout << "    geef huisnummer: ";
			cin >> huisnummer;
			cout << "    geef gemeente: ";
			cin >> gemeente;
			cout << "    prioriteit? 0 of 1: ";
			cin >> prioriteit;
			cout << "    geef lengte vd pakket: ";
			cin >> lengte;
			cout << "    geef breedte vd pakket: ";
			cin >> breedte;
			Pakket p (userId,voornaam,achternaam,straat,huisnummer,gemeente,prioriteit,lengte,breedte);
			PAKKET.addPakket(p);
		} break;

		case 2: {
			int id;
			cout << "    geef de voertuig id: ";
			cin >> id;
			VOERTUIG.archieveVoertuig(id);
		} break;
		}

	} while (keuze != 0);
	return keuze;
}