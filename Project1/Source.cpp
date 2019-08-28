#include <iostream>
#include "Encryptie.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
using namespace std;
using namespace mysqlx;


//klassen includen
#include "Voertuig.h"
#include "Pakket.h"

//globale session variabele

Session session = Database::getSession();
Schema schema = session.getSchema("1819IP_groep14");

//alle database tabellen voor de menu stukken
Table tableVoertuig = schema.getTable("L9_Voertuig");
Table tablePakket = schema.getTable("L9_Pakket");
Table tableLogin = schema.getTable("L9_Login");
Table tableWerknemer = schema.getTable("L9_Werknemer");
Table tableLog = schema.getTable("L9_Log");

//encryptie variabele om de functies ervan op te roepen
Encryptie encryptie;

//de ingelogde werknemer voor de logging
std::string werknemer;
const std::string KEY = "Ali_L9_Solo_Carry";

//functie om elke actie te loggen naar de database
void log(std::string gebeurtenis);

//functie om een csv bestand met paketten uit te lezen
//en in de database te stoppen
void importPakketCsv(std::string bestandsnaam);
void exportCsv(std::string bestandsnaam);

//menu items
int hoofdMenu();
int voertuigMenu();
int pakketMenu();
int ladingMenu();
int voertuigDetailMenu();
int statistiekenMenu();
int pakketDetailMenu();
int werknemerMakenMenu();
int csvEnBackupMenu();
int logsMenu();

int main()
{
	exportCsv("testing.csv");

	std::string username;
	std::string password;
	cout << "    login: " << endl;
	cout << "    geef je username in: ";
	getline(cin, username);
	cout << "    geef je password in: ";
	getline(cin, password);
	while (!encryptie.checkLogin(username, password)) {
		cout << "    foute username/ wachtwoord, probeer opnieuw: " << endl;
		cout << "    geef aub je username in: ";
		getline(cin, username);
		cout << "    geef aub je wachtwoord in: ";
		getline(cin, password);
	};

	werknemer = encryptie.EMPLOYEE;
	std::string msg = "aanglogt op het systeem";
	log(msg);

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
		case 5: statistiekenMenu();
			break;
		case 6: pakketDetailMenu();
			break;
		case 7: werknemerMakenMenu();
			break;
		case 8: csvEnBackupMenu();
			break;
		case 9: logsMenu();
			break;
		
		}
	} while (keuze != 0);
	msg = "uitgelogt van het systeem";
	log(msg);
	//typical return 0; vd main functie
	return 0;
}

void log(std::string gebeurtenis)
{
	tableLog.insert("name", "text").values(werknemer, gebeurtenis).execute();
}

void importPakketCsv(std::string bestandsnaam)
{
	ifstream bestand(bestandsnaam);

	std::string id;
	std::string voertuigId;
	std::string userId;
	std::string status;
	std::string opmerking;
	std::string capaciteit;
	std::string prioriteit;
	std::string voornaam;
	std::string achternaam;
	std::string straat;
	std::string huisnummer;
	std::string gemeente;
	std::string actief;


	while (bestand.good()) {

		getline(bestand, id, ',');
		getline(bestand, voertuigId, ',');
		getline(bestand, userId, ',');
		getline(bestand, status, ',');
		getline(bestand, opmerking, ',');
		getline(bestand, capaciteit, ',');
		getline(bestand, prioriteit, ',');
		getline(bestand, voornaam, ',');
		getline(bestand, achternaam, ',');
		getline(bestand, straat, ',');
		getline(bestand, huisnummer, ',');
		getline(bestand, gemeente, ',');
		getline(bestand, actief, '\n');

		std::cout << "    Id: " << id << '\n';
		std::cout << "    VoertuigId: " << voertuigId << '\n';
		std::cout << "    UserId: " << userId << '\n';
		std::cout << "    Status: " << status << '\n';
		std::cout << "    Opmerking: " << opmerking << '\n';
		std::cout << "    Capaciteit: " << capaciteit << '\n';
		std::cout << "    Prioriteit: " << prioriteit << '\n';
		std::cout << "    Voornaam: " << voornaam << '\n';
		std::cout << "    Achternaam: " << achternaam << '\n';
		std::cout << "    Straat: " << straat << '\n';
		std::cout << "    Huisnummer: " << huisnummer << '\n';
		std::cout << "    Gemeente: " << gemeente << '\n';
		std::cout << "    Actief: " << actief << '\n';
		std::cout << "    -------------------" << '\n';

		try {
			tablePakket.insert("id", "voertuigId", "userId", "status", "opmerking", "capaciteit", "prioriteit", "voornaam", "achternaam", "straat", "huisnummer", "gemeente", "actief").values(
				id, voertuigId, userId, status, opmerking, capaciteit, prioriteit, voornaam, achternaam, straat, huisnummer, gemeente, actief).execute();
		}
		catch (mysqlx::Error e) {
			std::cout << "    " << e.what() << std::endl;
		}
		
	}
	bestand.close();
}

void exportCsv(std::string bestandsnaam) {
	ofstream bestand;
	bestand.open(bestandsnaam);
	bestand << 1 << "tamara" << endl;
	bestand.close();

}

//menu items
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
		cout << "    7. werknemer toevoegen" << endl;
		cout << "    8. csv en backup" << endl;
		cout << "    9. logs" << endl;
		cout << "    0. sluiten" << endl << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;

		if ((keuze < 0) || (keuze > 9)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while (((keuze < 0) || (keuze > 9)));
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
		cout << "    3. gemiddelde capaciteit van paketten" << endl;
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

int werknemerDetails() {
	int keuze;
	do {
		cout << "    1. maak een nieuwe werknemer" << endl;
		cout << "    0. terug" << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;
		if ((keuze < 0) || (keuze > 1)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while ((keuze < 0) || (keuze > 1));
	return keuze;
}

int csvEnBackupDetails() {
	int keuze;
	do {
		cout << "    1. pakket importeren uit csv" << endl;
		cout << "    2. backup maken" << endl;
		cout << "    3. backup terugzetten" << endl;
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

int logDetails() {
	int keuze;
	do {
		cout << "    1. logs bekijken" << endl;
		cout << "    0. terug" << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;
		if ((keuze < 0) || (keuze > 1)) {
			cout << "    ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while ((keuze < 0) || (keuze > 1));
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
			try {

				tableVoertuig.insert("naam", "totaalCapaciteit", "beschikbaarCapaciteit").values(name, capaciteit, capaciteit).execute();
			}
			catch (mysqlx::Error e) {
				std::cout << "    " << e.what() << std::endl;
			}
			
			std::string msg = "voertuig " + name + " toegevoegt";
			log(msg);
		} break;

		case 2: {
			int id;
			cout << "    geef de voertuig id: ";
			cin >> id;
			try {

				tableVoertuig.update().set("actief", 0).where("id = :param").bind("param", id).execute();
			}
			catch (mysqlx::Error e) {
				std::cout << "    " << e.what() << std::endl;
			}

			
			std::string msg = "voertuigid " + to_string(id) + " opgezocht";
			log(msg);
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

				cout << row[0] << " - ";
			
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

			try {
				tablePakket.insert("userId", "status", "capaciteit", "prioriteit", "voornaam", "achternaam", "straat", "huisnummer", "gemeente", "actief").values(
					p.getUserId(), "in magazijn", p.getCapaciteit(), p.getPrioriteit(), p.getVoornaam(), p.getAchternaam(), p.getStraat(), p.getHuisnummer(), p.getGemeente(), 1).execute();

			}
			catch (mysqlx::Error e) {
				std::cout << "    " << e.what() << std::endl;
			}
		
			std::string msg = "pakket toegevoegt";
			log(msg);
		} break;

		case 2: {
			int id;
			cout << "    geef de paket id: ";
			cin >> id;

			try {
				tablePakket.update().set("actief", 0).where("id = :param").bind("param", id).execute();

			}
			catch (mysqlx::Error e) {
				std::cout << "    " << e.what() << std::endl;
			}
			
			std::string msg = "paket " + to_string(id) + " gearchiveerd";
			log(msg);
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
			std::string msg = "voertuigen vullen geklikt";
			log(msg);

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
						try {

							tableVoertuig.update().set("status", "onderweg").where("id = :param").bind("param", voertuigen[i].getId()).execute();
						}
						catch (mysqlx::Error e) {
							std::cout << "    " << e.what() << std::endl;
						}
						
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
			std::string msg = "voertuig overzicht tonen geklikt";
			log(msg);
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
		switch (keuze) {
		case 1: {
			mysqlx::RowResult result1 = tableVoertuig.select("*").where("actief = 1").execute();
			cout << "    beschikbare ids: ";
			for (mysqlx::Row row : result1.fetchAll()) {

				cout << row[0] << " - ";

			}
			int id;
			cout << "    " << "geef de voertuigId in: ";
			cin >> id;
			std::string status;
			std::string msg = "voertuigdetails geklikt van " + to_string(id);
			log(msg);
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
			mysqlx::RowResult result1 = tableVoertuig.select("*").where("actief = 1").execute();
			cout << "    beschikbare ids: ";
			for (mysqlx::Row row : result1.fetchAll()) {

				cout << row[0] << " - ";

			}
			int id;
			std::string status;
			cout << "    geef de paket id ";
			cin >> id;
			cout << "    geef de nieuwe status ";
			cin >> status;

			try {
				tablePakket.update().set("status", status).where("id = :param").bind("param", id).execute();

			}
			catch (mysqlx::Error e) {
				std::cout << "    " << e.what() << std::endl;
			}
			
			std::string msg = "status gewijzigt van voertuig " + to_string(id) + " naar " + status;
			log(msg);
		} break;
		}

	} while (keuze != 0);
	return keuze;
}

int statistiekenMenu() {
	cout << "    | statistiekenmenu |    " << endl << endl;
	int keuze;
	do {
		keuze = statistiekenLijsten();
		switch (keuze) {
		case 1: {
			std::string msg = "eerste statistiek geklikt";
			log(msg);
			//beschikbare klanten ids, eene kiezen
			mysqlx::RowResult result1 = tableLogin.select("*").where("type = 'klant'").execute();
			cout << "    beschikbare ids: ";
			for (mysqlx::Row row : result1.fetchAll()) {

				cout << row[0] << " - ";

			}
			cout << "    geef een id in:  ";
			int id;
			cin >> id;
		
			mysqlx::RowResult result = tablePakket.select("*").where("userId = :param").bind("param", id).execute();
			cout << "    alle paketten van klantid " << id << ":" << endl;
			for (mysqlx::Row row : result.fetchAll()) {

				cout << "    pakket id: " << row[0] << ", " << row[7] << " " << row[8] << " ," << row[9] << " " << row[10] << " "<< row[11] << " " << endl;

			}
		} break;

		case 2: {
			std::string msg = "tweede statistiek geklikt";
			log(msg);
			//beschikbare gemeenten ids, eene kiezen
			mysqlx::RowResult result = tablePakket.select("gemeente").execute();
			cout << "    beschikbare gemeenten: " << endl;
			for (mysqlx::Row row : result.fetchAll()) {

				cout << "    " << row[0] << endl;

			} 
			cout << endl;
			cout << "    geef een gemeente:  ";
			std::string gemeente;
			cin >> gemeente;

			mysqlx::RowResult res = tablePakket.select("*").where("gemeente = :param").bind("param", gemeente).execute();
			for (mysqlx::Row row : res.fetchAll()) {

				cout << "    pakket id: " << row[0] << ", " << row[7] << " " << row[8] << " ," << row[9] << " " << row[10] << " " << row[11] << " " << endl;

			}
			
		} break;

		case 3: {
			std::string msg = "derde statistiek geklikt";
			log(msg);
			//bgemiddelde capaciteit v/e pakket

			mysqlx::RowResult myResult = tablePakket.select("AVG(capaciteit)").execute();
			for (mysqlx::Row row : myResult.fetchAll()) {
				cout << "    gemiddelde capaciteit van een pakket bedraagt "<< row[0] << "m2" << endl;
			}

		} break;
		}

	} while (keuze != 0);
	return keuze;
}

int pakketDetailMenu() {
	cout << "    | pakketmenu |    " << endl << endl;
	int keuze;
	do {
		keuze = pakketDetails();
		switch (keuze) {
		case 1: {
			mysqlx::RowResult result1 = tablePakket.select("*").where("actief = 1").execute();
			cout << "    beschikbare ids: ";
			for (mysqlx::Row row : result1.fetchAll()) {

				cout << row[0] << " - ";

			}
			int id;
			std::string msg = "status van paket " + to_string(id) + " opgezocht";
			log(msg);
			cout << "    " << "geef de pakketId in: ";
			cin >> id;
			std::string status;
			mysqlx::RowResult res = tablePakket.select("status").where("id = :param").bind("param", id).execute();
			for (mysqlx::Row row : res.fetchAll()) {

				cout << "    status ervan is: " << row[0] << endl;

			}
		
		} break;

		case 2: {
			mysqlx::RowResult result1 = tablePakket.select("*").where("actief = 1").execute();
			cout << "    beschikbare ids: ";
			for (mysqlx::Row row : result1.fetchAll()) {

				cout << row[0] << " - ";

			}
			int id;
			std::string status;
			cout << "    geef de paket id ";
			cin >> id;
			cout << "    geef de nieuwe status bv. In magazijn, In verwerking, Onderweg, Geleverd, …";
			cin >> status;

			try {
				tablePakket.update().set("status", status).where("id = :param").bind("param", id).execute();

			}
			catch (mysqlx::Error e) {
				std::cout << "    " << e.what() << std::endl;
			}
	
			std::string msg = "status van paket " + to_string(id) + " gewijzigt naar " + status;
			log(msg);
		} break;
		}

	} while (keuze != 0);
	return keuze;
}

int werknemerMakenMenu() {
	cout << "    | werknemer creatie menu |    " << endl << endl;
	int keuze;
	do {
		keuze = werknemerDetails();
		switch (keuze) {
		case 1: {
			try {
				encryptie.make_employee();

			}
			catch (mysqlx::Error e) {
				std::cout << "    " << e.what() << std::endl;
			}
			
			std::string msg = "nieuwe werknemer aangemaakt";
			log(msg);

		} break;
		}

	} while (keuze != 0);
	return keuze;
}

int csvEnBackupMenu() {
	cout << "    | csv en backup |    " << endl << endl;
	int keuze;
	do {
		keuze = csvEnBackupDetails();
		switch (keuze) {
		case 1: {
			cout << "    geef aub de bestandsnaam in (bv: invoerbestand.csv):  ";
			std::string bestandsnaam;
			cin.ignore();
			getline(cin, bestandsnaam);
			importPakketCsv(bestandsnaam);

			std::string msg = "csv pakket geimporteerd";
			log(msg);

		} break;
		case 2: {
			//basically gaan we elke tabel vd database binnenhalen en dan per tabel alle rijen
			//opslaan in een csv bestand
			cout << "    de backups worden gemaakt en vind je terug onder de tableNaam met extensie csv:  " << endl;
			cout << "    dus bv L9_Voertuig.csv " << endl;

			//tabel voertuig
			ofstream bestand;
			bestand.open("L9_Voertuig.csv");
			
			mysqlx::RowResult result = tableVoertuig.select("*").execute();
			
			for (mysqlx::Row row : result.fetchAll()) {

				bestand << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << endl;

			}
			bestand.close();

			//tabel pakket
			ofstream bestand1;
			bestand1.open("L9_Pakket.csv");

			mysqlx::RowResult result1 = tablePakket.select("*").execute();

			for (mysqlx::Row row : result1.fetchAll()) {

				bestand1 << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << "," << row[6] << "," << row[7] << "," << row[8] << "," << row[9] << "," << row[10] << "," << row[11] << "," << row[12] << endl;

			}
			bestand1.close();

			//tabel login
			ofstream bestand2;
			bestand2.open("L9_Login.csv");
			mysqlx::RowResult result2 = tableLogin.select("*").execute();

			for (mysqlx::Row row : result2.fetchAll()) {

				bestand2 << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << endl;

			}
			bestand2.close();

			//tabel werknemer
			ofstream bestand3;
			bestand3.open("L9_Werknemer.csv");
			mysqlx::RowResult result3 = tableWerknemer.select("*").execute();

			for (mysqlx::Row row : result3.fetchAll()) {

				bestand3 << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << endl;

			}
			bestand3.close();

			//tabel logs
			ofstream bestand4;
			bestand4.open("L9_Log.csv");
			mysqlx::RowResult result4 = tableLog.select("*").execute();

			for (mysqlx::Row row : result4.fetchAll()) {

				bestand4 << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << endl;

			}
			bestand4.close();
			cout << "    alles succesvol gebackuped" << endl;
			std::string msg = "backup gemaakt/geexporteerd";
			log(msg);

		} break;
		case 3: {
			//voertuig tabel terugzetten
			ifstream bestand("L9_Voertuig.csv");

			std::string id;
			std::string naam;
			std::string status;
			std::string totaalCapaciteit;
			std::string beschikbaarCapaciteit;
			std::string actief;

			while (bestand.good()) {

				getline(bestand, id, ',');
				getline(bestand, naam, ',');
				getline(bestand, status, ',');
				getline(bestand, totaalCapaciteit, ',');
				getline(bestand, beschikbaarCapaciteit, ',');
				getline(bestand, actief, '\n');

				try {
					tableVoertuig.insert("id", "naam", "status", "totaalCapaciteit", "beschikbaarCapaciteit", "actief").values(
						id, naam, status, totaalCapaciteit, beschikbaarCapaciteit, actief).execute();
				}
				//het geeft cdk error op id maar alles werkt zonder problemen
				catch (mysqlx::Error e) {
					std::cout << "    " << e.what() << std::endl;
				}

			} 


			//pakket tabel terugzetten
			ifstream bestand1("L9_Pakket.csv");

			std::string id1;
			std::string voertuigId;
			std::string userId;
			std::string status1;
			std::string opmerking;
			std::string capaciteit;
			std::string prioriteit;
			std::string voornaam;
			std::string achternaam;
			std::string straat;
			std::string huisnummer;
			std::string gemeente;
			std::string actief1;

			while (bestand1.good()) {

				getline(bestand1, id1, ',');
				getline(bestand1, voertuigId, ',');
				getline(bestand1, userId, ',');
				getline(bestand1, status1, ',');
				getline(bestand1, opmerking, ',');
				getline(bestand1, capaciteit, ',');
				getline(bestand1, prioriteit, ',');
				getline(bestand1, voornaam, ',');
				getline(bestand1, achternaam, ',');
				getline(bestand1, straat, ',');
				getline(bestand1, huisnummer, ',');
				getline(bestand1, gemeente, ',');
				getline(bestand1, actief1, '\n');

				try {
					tablePakket.insert("id", "voertuigId", "userId", "status", "opmerking", "capaciteit", "prioriteit", "voornaam", "achternaam", "straat", "huisnummer", "gemeente", "actief").values(
						id1, voertuigId, userId, status1, opmerking, capaciteit, prioriteit, voornaam, achternaam, straat, huisnummer, gemeente, actief1).execute();
				}
				catch (mysqlx::Error e) {
					std::cout << "    " << e.what() << std::endl;
				}
			}


			//login tabel terugzetten
			ifstream bestand2("L9_Login.csv");

			std::string id2;
			std::string email;
			std::string password;
			std::string type;


			while (bestand2.good()) {

				getline(bestand2, id2, ',');
				getline(bestand2, email, ',');
				getline(bestand2, password, ',');
				getline(bestand2, type, '\n');


				try {
					tableLogin.insert("id", "email", "password", "type").values(
						id2, email, password, type).execute();
				}
				catch (mysqlx::Error e) {
					std::cout << "    " << e.what() << std::endl;
				}

			}

			//werknemer tabel terugzetten
			ifstream bestand3("L9_Werknemer.csv");

			std::string id3;
			std::string user;
			std::string salt;
			std::string hash;


			while (bestand3.good()) {

				getline(bestand3, id3, ',');
				getline(bestand3, user, ',');
				getline(bestand3, salt, ',');
				getline(bestand3, hash, '\n');


				try {
					tableWerknemer.insert("id", "user", "salt", "hash").values(
						id3, user, salt, hash).execute();
				}
				catch (mysqlx::Error e) {
					std::cout << "    " << e.what() << std::endl;
				}

			}

			//log tabel terugzetten
			ifstream bestand4("L9_Log.csv");

			std::string id4;
			std::string name;
			std::string text;
			std::string datum;


			while (bestand4.good()) {

				getline(bestand4, id4, ',');
				getline(bestand4, name, ',');
				getline(bestand4, text, ',');
				getline(bestand4, datum, '\n');


				try {
					tableLog.insert("id", "name", "text", "datum").values(
						id4, name, text, datum).execute();
				}
				catch (mysqlx::Error e) {
					std::cout << "    " << e.what() << std::endl;
				}
			}
			cout << "    succesvol de backup geimporteerd" << endl;
			std::string msg = "backup geimporteerd";
			log(msg);

		} break;
		}

	} while (keuze != 0);
	return keuze;
}

int logsMenu() {
	cout << "    | logs menu |    " << endl << endl;
	int keuze;
	do {
		keuze = logDetails();
		switch (keuze) {
		case 1: {
			mysqlx::RowResult result = tableLog.select("*").execute();
			for (mysqlx::Row row : result.fetchAll()) {
				std::string tijd = row[3];
				//std::string tijdStr = encryptie.time_t_to_string(tijd);
				cout << "    LogId: " << row[0] << endl;
				cout << "    Werknemer: " << row[1] << endl;
				cout << "    Actie: " << row[2] << endl;
				cout << "    Datum: " << row[3] << endl;
				cout << "    _____________________________" << endl;

			}
			std::string msg = "logs bekeken";
			log(msg);
			
		} break;
		}

	} while (keuze != 0);
	return keuze;
}
