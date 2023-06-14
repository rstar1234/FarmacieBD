#pragma once
#include <iostream>
#include <vector>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Medicament.h"
#include "Furnizor.h"

void afisareMedicamente(std::vector<std::vector<std::string>> deAfisat);
void afisareFurnizori(std::vector<std::vector<std::string>> deAfisat);
void getMedicamente();
int getMedicamentDupaNumeSt(std::vector<Medicament> medicamente, std::string nume_stiintific);
int getMedicamentDupaID(std::vector<Medicament> medicamente, int id);
void cautareDupaNumeComercial(std::vector<Medicament> medicamente);
void cautareDupaNumeStiintific(std::vector<Medicament> medicamente);
void cautareDupaAfectiuneaTratata(std::vector<Medicament> medicamente);
void cautareDupaProducator(std::vector<Medicament> medicamente);
void cautareDupaPret(std::vector<Medicament> medicamente);
void cautareDupaFurnizorMedicament(std::vector<Medicament> medicamente);
void cautareDupaDataFabricarii(std::vector<Medicament> medicamente);
void cautareDupaDataExpirarii(std::vector<Medicament> medicamente);
void stergeMedicament(std::vector<Medicament> medicamente);
void ModificaNumeStMedicament(std::vector<Medicament> medicamente);
void ModificaNumeComMedicament(std::vector<Medicament> medicamente);
void ModificaProducatorMedicament(std::vector<Medicament> medicamente);
void ModificaPretMedicament(std::vector<Medicament> medicamente);
void ModificaAfectiuneTratataMedicament(std::vector<Medicament> medicamente);
void ModificaFurnizorIDMedicament(std::vector<Medicament> medicamente);
void addMedicament(std::vector<Medicament> medicamente);
void FiltrareAnteturiMedicamente(std::vector<Medicament> medicamente);
std::vector<bool> verificaNulitatea(Medicament medicament);
  
void getFurnizori();
int getFurnizorDupaNume(std::vector<Furnizor> furnizori, std::string nume);
int getFurnizorDupaID(std::vector<Furnizor> furnizori, int id);
void addFurnizor(std::vector<Furnizor> furnizori);
void cautareDupaNumeFurnizor(std::vector<Furnizor> furnizori);
void cautareDupaIDFurnizor(std::vector<Furnizor> furnizori);
void cautareDupaAdresaFurnizor(std::vector<Furnizor> furnizori);
void cautareDupaNumarDeTelefonFurnizor(std::vector<Furnizor> furnizori);
void ModificaNumeFurnizor(std::vector<Furnizor> furnizori);
void ModificaAdresaFurnizor(std::vector<Furnizor> furnizori);
void ModificaNumarDeTelefonFurnizor(std::vector<Furnizor> furnizori);
void stergeFurnizor(std::vector<Furnizor> furnizori);
void FiltrareAnteturiFurnizori(std::vector<Furnizor>);

//void connectToDatabase(sql::Driver* driver, sql::Connection* con);
/*to do:
1. move functions to a different file that isn't a class*/