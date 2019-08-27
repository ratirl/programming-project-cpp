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
int voertuigDetailMenu();
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
		case 4: voertuigDetailMenu();
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
			tableVoertuig.insert("naam", "totaalCapaciteit", "beschikbaarCapaciteit").values(name, capaciteit, capaciteit).execute();
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
			mysqlx::RowResult result1 = tableLogin.select("*").where("actief = 1").execute();
			cout << "    beschikbare ids: ";
			for (mysqlx::Row row : result1.fetchAll()) {

				cout << row[0] << ",";
			
			}
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
			//stap 0: vector maken met de voertuigen die standby zijn
			//stap 1: vector maken met alle paketten die de status 'in magazijn' of 'in verwerking' hebben
			//stap 2: vector ordenen op gemeente 
			//stap 3: controleren of de beschikbare capaciteit van een voertuig >= de capaciteit vd bovenvermelde set
			//stap 4: de paketten uit de vector halen en hun status veranderen naar onderweg

			//stap 0//
			std::vector<Voertuig> voertuigen;
			std::string query = "    status = 'standby' and actief = 1";
			mysqlx::RowResult result1 = tableVoertuig.select("*").where(query).execute();
			cout << "    alle voertuigen beschikbaar voor gebruik:" << endl;
			for (mysqlx::Row row : result1.fetchAll()) {

				Voertuig v(row[0], row[1], row[2], row[3], row[4], row[5]);
				voertuigen.push_back(v);
				
				cout << "    " << v.getNaam() << endl;
			}
			//stap1// + stap 2//
			std::vector<Pakket> q;
			std::string qry = "    status = 'in magazijn' OR status = 'in verwerking'";
			cout << "    alle paketten in de queueue:" << endl;
			mysqlx::RowResult myResult = tablePakket.select("*").where(qry).orderBy("gemeente").execute();
			for (mysqlx::Row row : myResult.fetchAll()) {
			
				Pakket p(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11], row[12]);
				q.push_back(p);
				cout << "    " <<p.getId() << " - " << p.getVoornaam() << " - " << p.getAchternaam() << endl;
				
			}
			//stap3 
			//voor elke voertuig dat nog niet onderweg (dus standby)
			//weten we dat dit nog plaats over heeft dus
			for (int i = 0; i < voertuigen.size(); i++){
				cout << "    we zijn bezig met " << voertuigen[i].getNaam() << " in te vullen" << endl;
				//kijken we voor elk voertuig 
				for (int j = 0; j < q.size(); j++) {
					//dan veranderen we de status naar onderweg en 
					//loopen we terug af met de volgende auto
					if (voertuigen[i].getBeschikbaarCapaciteit() < q[j].getCapaciteit()) {
						cout << "deze voertuig heeft geen plaats meer," << endl;
						cout << "we beginnen met de volgende voertuig te vullen";
						tableVoertuig.update().set("status", "onderweg").where("id = :param").bind("param", voertuigen[i].getId()).execute();
					}
					//in dit geval heeft de voertuig dus wel nog plaats dus gaan we de pakket erin steken
					else {
						if (q[j].getStatus() == "in magazijn" || q[j].getStatus() == "in verwerking") {
							//we zetten de status vd pakket op onderweg en zetten bij voertuidId de id vd huidige voertuig
							tablePakket.update().set("status", "onderweg").where("id = :param").bind("param", q[j].getId()).execute();
							tablePakket.update().set("voertuigId", voertuigen[i].getId()).where("id = :param").bind("param", q[j].getId()).execute();
							//en verminderen de beschikbare capaciteit vd huidige voertuig met de capaciteit vd pakket
							voertuigen[i].verminderBeschikbaarCapaciteit(q[j].getCapaciteit());
							tableVoertuig.update().set("beschikbaarCapaciteit", voertuigen[i].getBeschikbaarCapaciteit()).where("id = :param").bind("param", voertuigen[i].getId()).execute();
							q[j].setStatus("onderweg");
						}
					}
				}
			}
			
		} break;

		case 2: { //toon overzicht van elke voertuig met de lading dat ze moeten hebben
			
			vector<Voertuig> voertuigen;
			mysqlx::RowResult result = tableVoertuig.select("*").where("totaalCapaciteit != beschikbaarCapaciteit").execute();
			for (mysqlx::Row row : result.fetchAll()) {

				Voertuig v(row[0], row[1], row[2], row[3], row[4], row[5]);
				voertuigen.push_back(v);
		
			}

			for (int i = 0; i < voertuigen.size(); i++) {
				
				mysqlx::RowResult result1 = tablePakket.select("*").where("voertuigId = :param").bind("param", voertuigen[i].getId()).execute();
				cout << "    Voertuig " << voertuigen[i].getNaam() << " moet gevult worden met volgende paketten in volgorde:" << endl;
				for (mysqlx::Row row : result1.fetchAll()) {

					Pakket p(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11], row[12]);
					cout << "    "  << "pakket " << p.getId() << " van " << p.getVoornaam() << " " << p.getAchternaam() << " met bestemming" << p.getGemeente() << endl;

				} cout << endl;
			}
		} break;
		}

	} while (keuze != 0);
	return keuze;
}


int voertuigDetailMenu() {
	cout << "    | voertuigmenu |    " << endl << endl;
	int keuze;
	do {
		keuze = voertuigDetails();
		cout << "    1. toon status en paketten van voertuig x" << endl; //user geeft id in vd voertuig
		cout << "    2. editeer status van voertuig x" << endl; //update status vd voertuig
		cout << "    3. editeer pakket van voertuig x" << endl; //update pakket details vd voertuig
		cout << "    0. terug" << endl;
		switch (keuze) {
		case 1: {
			mysqlx::RowResult result1 = tableVoertuig.select("*").where("actief = 1").execute();
			cout << "    beschikbare ids: ";
			for (mysqlx::Row row : result1.fetchAll()) {

				cout << row[0] << ",";

			}
			int id;
			cout << "    " << "geef de voertuigId in: ";
			cin >> id;
			std::string status;
			mysqlx::RowResult res = tableVoertuig.select("status").where("id = :param").bind("param", id).execute();
			for (mysqlx::Row row : res.fetchAll()) {

				status = row[0];
				
			}
			vector<Pakket> paketten;
			mysqlx::RowResult result = tablePakket.select("*").where("voertuigId = :param").bind("param", id).execute();
			cout << "    voertuig met id " << id << " heeft als status " << status << ": en bevat volgene paketten:" << endl;
			for (mysqlx::Row row : result.fetchAll()) {

				Pakket p(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11], row[12]);
				cout << "    " << "pakket " << p.getId() << " van " << p.getVoornaam() << " " << p.getAchternaam() << " met bestemming " << p.getGemeente() << " en capaciteit " << p.getCapaciteit() <<"m2 en status:" << p.getStatus() << endl;

			}

		} break;

		case 2: {
			int id;
			std::string status;
			cout << "    geef de paket id ";
			cin >> id;
			cout << "    geef de nieuwe status ";
			cin >> status;
			tablePakket.update().set("status", status).where("id = :param").bind("param", id).execute();
		} break;
		}

	} while (keuze != 0);
	return keuze;
}