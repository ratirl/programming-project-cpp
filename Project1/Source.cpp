#include <iostream>
#include "Database.h"
using namespace std;
using namespace mysqlx;

//klassen includen
#include "Voertuig.h"
#include "Pakket.h"

//globale session variabele
Session session = Database::getSession();
Schema schema = session.getSchema("1819IP_groep14");

//alle database tabellen
Table tableVoertuig = schema.getTable("L9_Voertuig");
Table tablePakket = schema.getTable("L9_Pakket");
Table tableLogin = schema.getTable("L9_Login");

//menu items
int hoofdMenu();
int voertuigMenu();
int pakketMenu();
int ladingMenu();
int voertuigDetails();
int statistiekenLijsten();
int pakketDetails();

int main()
{
	//vooor archiveren
	//table.update().set("actief", 0).where("id = :param").bind("param", id).execute();
	//tableVoertuig.insert("naam", "totaalCapaciteit").values("WORKS", 20).execute();

	//begin menu
	int keuze;
	do {
		keuze = hoofdMenu();
		switch (keuze) {
		case 1: voertuigMenu();
			break;
		case 2: pakketMenu();
			break;
		case 3: ladingMenu();
			break;
		case 4: voertuigDetails();
			break;
		case 5: statistiekenLijsten();
			break;
		case 6: pakketDetails();
			break;
		}
	} while (keuze != 0);

	//typical return 0; vd main functie
	return 0;
}

int hoofdMenu()
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

int voertuigenInbrengen() {

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

int bestellingenInbrengen() {
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

int lijstVoertuigLading() {
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


int voertuigDetails() {
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

int statistiekenLijsten() {
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

int pakketDetails() {
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


int voertuigMenu() {
	cout << "    | voertuigmenu |    " << endl << endl;
	int keuze;
	do {
		keuze = voertuigenInbrengen();
		switch (keuze) {
		case 1: {

			std::string name;
			double capaciteit;
			cout << "    geef de naam van de auto in: ";
			cin >> name;
			cout << "    geef de capaciteit in in m2: ";
			cin >> capaciteit;
			cin.ignore();
			tableVoertuig.insert("naam", "totaalCapaciteit").values(name, capaciteit).execute();
		} break;

		case 2: {
			int id;
			cout << "    geef de voertuig id: ";
			cin >> id;
			tableVoertuig.update().set("actief", 0).where("id = :param").bind("param", id).execute();
		} break;
		}

	} while (keuze != 0);
	return keuze;
}

int pakketMenu() {
	cout << "    | pakketmenu |    " << endl << endl;
	int keuze;
	do {
		keuze = bestellingenInbrengen();
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
			cout << "    geef lengte vd pakket in m2: ";
			cin >> lengte;
			cout << "    geef breedte vd pakket: m2 ";
			cin >> breedte;
			Pakket p (userId, voornaam, achternaam, straat, huisnummer, gemeente, prioriteit, lengte, breedte);
			tablePakket.insert("userId", "status", "capaciteit", "prioriteit", "voornaam", "achternaam", "straat", "huisnummer", "gemeente", "actief").values(
			p.getUserId() , "in magazijn", p.getCapaciteit(), p.getPrioriteit(), p.getVoornaam(), p.getAchternaam(), p.getStraat(), p.getHuisnummer(), p.getGemeente(), 1).execute();
		} break;

		case 2: {
			int id;
			cout << "    geef de paket id: ";
			cin >> id;
			tablePakket.update().set("actief", 0).where("id = :param").bind("param", id).execute();
		} break;
		}

	} while (keuze != 0);
	return keuze;
}


int ladingMenu() {
	cout << "    | ladingmenu |    " << endl << endl;
	int keuze;
	do {
		keuze = lijstVoertuigLading();
		switch (keuze) {
		case 1: { //vul voertuigen
			//stap 1: vector maken met alle paketten die de status 'in magazijn' of 'in verwerking' hebben
			//stap 2: vector ordenen op gemeente 
			//stap 3: controleren of de beschikbare capaciteit van een voertuig >= de capaciteit vd bovenvermelde set
			//stap 4: de paketten uit de vector halen en hun status veranderen naar onderweg

			//stap1// + stap 2//
			std::vector<Pakket> q;
			std::string qry = "status = 'in magazijn' OR status = 'in verwerking'";
			mysqlx::RowResult myResult = tablePakket.select("*").where(qry).orderBy("gemeente").execute();
			for (mysqlx::Row row : myResult.fetchAll()) {
			
				Pakket p(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11], row[12]);
				cout << p.getGemeente() << endl;
			}
			//stap3 
			for (int i = 0; i < q.size(); i++) {

			}
			
		} break;

		case 2: { //toon overzicht van elke voertuig met de lading dat ze moeten hebben
			int id;
			cout << "    geef de voertuig id: ";
			cin >> id;
			tableVoertuig.update().set("actief", 0).where("id = :param").bind("param", id).execute();
		} break;
		}

	} while (keuze != 0);
	return keuze;
}