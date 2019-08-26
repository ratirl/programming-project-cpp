#include "MenuItems.h"

int MenuItems::hoofdMenu()
{
	int keuze;
	do {
		cout << "    Welkom.    " << endl << endl;
		cout << "    1. voertuigen inbrengen" << endl;
		cout << "    2. bestellingen inbrengen" << endl;
		cout << "    3. lijst voertuig met lading" << endl;
		cout << "    4. detals voertuig" << endl;
		cout << "    5. statistieken lijsten" << endl << endl;
		cout << "    6. detals pakket" << endl;
		cout << "    0. sluitenn" << endl << endl;
		cout << "    type je keuze in: ";
		cin >> keuze;
		cout << endl;

		if ((keuze < 0) || (keuze > 6)) {
			cout << "    Ongeldige invoer, kies openieuw." << endl << endl;
		}
	} while (((keuze < 0) || (keuze > 6)));
	return keuze;
}
