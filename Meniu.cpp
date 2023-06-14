#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "Medicament.h"
#include "Furnizor.h"
#include "FarmacieBD.h"
#include "Meniuri.h"

int main() {
	std::vector<Medicament> medicamente;
	Medicament medicament;
	Furnizor furnizor;
	std::vector<Furnizor> furnizori;
	char optiuneGenerala, optiuneMedicamente, optiuneFurnizori;
	while (true) {
		system("CLS");
		system("Color 0D");
		std::cout << "1. Optiuni pentru medicamente\n";
		std::cout << "2. Optiuni pentru furnizori\n";
		std::cout << "X. Exit\n";
		std::cout << "Alegeti o optiune: \n";
		//add more options
		std::cin >> optiuneGenerala;
		switch (optiuneGenerala) {
			case '1':
				while (true) {
					optiuni();
					std::cin >> optiuneMedicamente;
					if (optiuneMedicamente == 'X')
						break;
					switch (optiuneMedicamente) {
					case '1':
						getMedicamente();
						_getch();
						break;
					case '2':
						cautareMedicamente(medicament, medicamente);

						break;
					case '3':
						modificareMedicamente(medicament, medicamente);

						break;
					case '4':
						addMedicament(medicamente);
						_getch();
						break;
					case '5':
						stergeMedicament(medicamente);
						_getch();
						break;

					default:
						std::cout << "Nu exista aceasta optiune!\n";
						_getch();
						break;
					}
					break;
				}
				break;
			case '2':
				while (true) {
					optiuni();
					std::cin >> optiuneFurnizori;
					if (optiuneFurnizori == 'X')
						break;
					switch (optiuneFurnizori) {
						case '1':
							getFurnizori();
							_getch();
							break;
						case '2':
							cautareFurnizori(furnizor, furnizori);
							_getch();
							break;
						case '3':
							modificareFurnizori(furnizor, furnizori);
							_getch();
							break;
						case '4':
							addFurnizor(furnizori);
							break;
						case '5':
							stergeFurnizor(furnizori);
							break;
						default:
							std::cout << "Nu exista aceaste optiune!\n";
							_getch();
							break;
					}
					break;
				}
				break;
			case 'X':
				exit(0);
				break;
			default:
				std::cout << "Nu exista aceasta optiune!\n";
				_getch();
				break;
		}
	} 
	return 0;
}