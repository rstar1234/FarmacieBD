#include <iostream>
#include "Medicament.h"
#include "FarmacieBD.h"
#include "Meniuri.h"
#include <conio.h>

void optiuni() {
	system("CLS");
	system("Color 09");
	std::cout << "1. Afisare\n";
	std::cout << "2. Cautare\n";
	std::cout << "3. Modificare\n";
	std::cout << "4. Adaugare\n";
	std::cout << "5. Stergere\n";
	std::cout << "X. Inapoi\n";
	std::cout << "Alegeti o optiune:\n";
}

void cautareMedicamente(Medicament medicament, std::vector<Medicament> medicamente) {
	char optiuneCautare;
	while (true)
	{
		system("CLS");
		system("Color 09");
		std::cout << "Dupa ce criteriu doriti sa efectuati cautarea?\n\n";
		std::cout << "1. Nume stiintific\n";
		std::cout << "2. Nume comercial\n";
		std::cout << "3. Producator\n";
		std::cout << "4. Pret\n";
		std::cout << "5. Afectiune tratata\n";
		std::cout << "6. Nume Furnizor\n";
		std::cout << "7. Data Fabricarii\n";
		std::cout << "8. Data Expirarii\n";
		std::cout << "9. ID Furnizor\n";
		std::cout << "X. Inapoi\n";
		std::cin >> optiuneCautare;
		if (optiuneCautare == 'X') {
			optiuni();
			_getch();
			break;
		}
		switch (optiuneCautare) {
		case '1':
			cautareDupaNumeStiintific(medicamente);
			_getch();
			break;
		case '2':
			cautareDupaNumeComercial(medicamente);
			_getch();
			break;
		case '3':
			cautareDupaProducator(medicamente);
			_getch();
			break;
		case '4':
			cautareDupaPret(medicamente);
			_getch();
			break;
		case '5':
			cautareDupaAfectiuneaTratata(medicamente);
			_getch();
			break;
		case '6':
			cautareDupaFurnizorMedicament(medicamente);
			_getch();
			break;
		case '7':
			cautareDupaDataFabricarii(medicamente);
			_getch();
			break;
		case '8':
			cautareDupaDataExpirarii(medicamente);
			_getch();
			break;
		case '9':
			ModificaFurnizorIDMedicament(medicamente);
			_getch();
			break;
		default:
			std::cout << "Nu exista aceasta optiune!";
			break;
		}
	}
}

void modificareMedicamente(Medicament medicament, std::vector<Medicament> medicamente) {
	char optiuneModificare;
	while (true) {
		system("CLS");
		system("Color 09");
		std::cout << "Ce doriti sa modificati?\n\n";
		std::cout << "1. Nume stiintific\n";
		std::cout << "2. Nume comercial\n";
		std::cout << "3. Producator\n";
		std::cout << "4. Pret\n";
		std::cout << "5. Afectiune tratata\n";
		std::cout << "X. Inapoi\n";
		while (true) {
			std::cin >> optiuneModificare;
			if (optiuneModificare == 'X') {
				optiuni();
				_getch();
				break;
			}
			switch (optiuneModificare) {
			case 1:
				ModificaNumeStMedicament(medicamente);
				_getch();
				break;
			case '2':
				ModificaNumeComMedicament(medicamente);
				_getch();
				break;
			case '3':
				ModificaProducatorMedicament(medicamente);
				_getch();
				break;
			case '4':
				ModificaPretMedicament(medicamente);
				_getch();
				break;
			case '5':
				ModificaAfectiuneTratataMedicament(medicamente);
				_getch();
				break;
				//do the other cases
			default:
				std::cout << "Nu exista aceasta optiune!\n";
				break;
			}
		}
	}
}

void cautareFurnizori(Furnizor furnizor, std::vector<Furnizor> furnizori) {
	char optiuneCautare;
	while (true) {
		system("CLS");
		system("Color 09");
		std::cout << "Dupa ce criteriu doriti sa efectuati cautarea?\n\n";
		std::cout << "1. ID\n";
		std::cout << "2. Nume\n";
		std::cout << "3. Adresa\n";
		std::cout << "4. Numar de telefon\n";
		std::cout << "X. Inapoi\n";
		std::cin >> optiuneCautare;
		if (optiuneCautare == 'X') {
			optiuni();
			_getch();
			break;
		}
		switch (optiuneCautare){	
			case '1':
				cautareDupaIDFurnizor(furnizori);
				_getch();
				break;
			case '2':
				cautareDupaNumeFurnizor(furnizori);
				_getch();
				break;
			case '3':
				cautareDupaAdresaFurnizor(furnizori);
				_getch();
				break;
			case '4':
				cautareDupaNumarDeTelefonFurnizor(furnizori);
				_getch();
				break;
			default:
				std::cout << "Nu exista aceasta optiune!\n";
				break;
		}
		//break;
	}
}

void modificareFurnizori(Furnizor furnizor, std::vector<Furnizor> furnizori) {
	char optiuneModificare;
	while (true) {
		system("CLS");
		system("Color 09");
		std::cout << "Ce doriti sa modificati?\n\n";
		std::cout << "1. Nume\n";
		std::cout << "2. Adresa\n";
		std::cout << "3. Numar de telefon\n";
		std::cout << "X. Inapoi\n";
		while (true) {
			std::cin >> optiuneModificare;
			if (optiuneModificare == 'X') {
				optiuni();
				_getch();
				break;
			}
			switch (optiuneModificare) {
				case '1':
					ModificaNumeFurnizor(furnizori);
					_getch();
					break;
				case '2':
					ModificaAdresaFurnizor(furnizori);
					_getch();
					break;
				case '3':
					ModificaNumarDeTelefonFurnizor(furnizori);
					_getch();
					break;
				default:
					std::cout << "Nu exista aceasta optiune!\n";
					break;
			}
		}
	}
}