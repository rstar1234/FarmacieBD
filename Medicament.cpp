#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Medicament.h"
#include "Connection.h"

Medicament::Medicament(int id=0, string nume_comercial="", string nume_stiintific="", string producator="", int pret=0, string data_fabricarii="", string data_expirarii="", string afectiune_tratata="", int furnizor_id=0) {
	MedicamentID = id;
	MedicamentNumeComercial = nume_comercial;
	MedicamentNumeStiintific = nume_stiintific;
	MedicamentProducator = producator;
	MedicamentPret = pret;
	MedicamentDataFabricarii = data_fabricarii;
	MedicamentDataExpirarii = data_expirarii;
	MedicamentAfectiuneTratata = afectiune_tratata;
	FurnizorID = furnizor_id;
}
Medicament::Medicament() {
	MedicamentNumeComercial = MedicamentNumeStiintific = MedicamentAfectiuneTratata = MedicamentDataExpirarii = MedicamentDataFabricarii = "";
	MedicamentID = MedicamentPret = FurnizorID = 0;
}

int Medicament::getID() {
	return MedicamentID;
}

string Medicament::getNumeComercial() {
	return MedicamentNumeComercial;
}

string Medicament::getNumeStiintific() {
	return MedicamentNumeStiintific;
}

string Medicament::getProducator() {
	return MedicamentProducator;
}

int Medicament::getPret() {
	return MedicamentPret;
}

string Medicament::getDataFabricarii() {
	return MedicamentDataFabricarii;
}

string Medicament::getDataExpirarii() {
	return MedicamentDataExpirarii;
}

string Medicament::getAfectiuneTratata() {
	return MedicamentAfectiuneTratata;
}

int Medicament::getFurnizorID()
{
	return FurnizorID;
}

void Medicament::setNumeComercial(string nume_comercial) {
	MedicamentNumeComercial = nume_comercial;
}

void Medicament::setNumeStiintific(string nume_stiintific) {
	MedicamentNumeStiintific = nume_stiintific;
}

void Medicament::setProducator(string producator) {
	MedicamentProducator = producator;
}

void Medicament::setPret(int pret) {
	MedicamentPret = pret;
}

void Medicament::setAfectiuneTratata(string afectiune_tratata) {
	MedicamentAfectiuneTratata = afectiune_tratata;
}

void Medicament::setFurnizorID(int furnizor_id)
{
	FurnizorID = furnizor_id;
}

/*Driver* driver;
Connection* con;*/

void Medicament::InitializareVector(vector<Medicament> medicamente) {

}