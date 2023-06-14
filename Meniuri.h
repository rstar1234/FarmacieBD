#pragma once
#include <iostream>
#include "Medicament.h"

void optiuni();
void cautareMedicamente(Medicament medicament, std::vector<Medicament> medicamente);
void modificareMedicamente(Medicament medicament, std::vector<Medicament> medicamente);
void cautareFurnizori(Furnizor furnizor, std::vector<Furnizor> furnizori);
void modificareFurnizori(Furnizor furnizor, std::vector<Furnizor> furnizori);