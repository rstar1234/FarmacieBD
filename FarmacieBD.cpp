#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Medicament.h"
#include "FarmacieBD.h"
#include "Connection.h"
#include <tabulate/table.hpp>

//con->setSchema("farmacie");
//stmt = con->createStatement();
/*result = stmt->executeQuery("SELECT * FROM medicamente");
while (result->next()) {
	cout << "id = " << result->getInt("ID") << endl;
	cout << "nume = " << result->getString("Nume") << endl;
	cout << "firma = " << result->getString("Firma") << endl;
	cout << "producator = " << result->getString("Producator") << endl;
}*/

//create a menu style application that allows CRUD operations
//to do: add the new class to the uml diagram

const int LATIME_MEDICAMENTE = 10;
const int LATIME_FURNIZORI = 25;

std::vector<bool> verificaNulitatea(Medicament medicament) {
	std::vector<bool> check;
	if (medicament.getID() != 0)
		check.push_back(1);
	else
		check.push_back(0);
		if (medicament.getNumeStiintific() != "")
			check.push_back(1);
		else
			check.push_back(0);
		if (medicament.getNumeComercial() != "")
			check.push_back(1);
		else
			check.push_back(0);

		if (medicament.getProducator() != "")
			check.push_back(1);
		else
			check.push_back(0);
		if (medicament.getPret() != 0)
			check.push_back(1);
		else
			check.push_back(0);
		if (medicament.getDataFabricarii() != "")
			check.push_back(1);
		else
			check.push_back(0);
		if (medicament.getDataExpirarii() != "")
			check.push_back(1);
		else
			check.push_back(0);
		if (medicament.getAfectiuneTratata() != "")
			check.push_back(1);
		else
			check.push_back(0);
		if (medicament.getFurnizorID() != 0)
			check.push_back(1);
		else
			check.push_back(0);
		return check;
}

bool eNulSauZero(string str) {
	//va fi folosita pentru stergere
	return str.empty() || str == "0";
}

int getMedicamentDupaID(std::vector<Medicament> medicamente, int id) {
	for (int i = 0; i < medicamente.size(); i++) {
		if (medicamente[i].getID() == id)
			return i;
	}
	return medicamente.size() + 1;
}

void FiltrareAnteturiMedicamente(std::vector<Medicament> medicamente) {
	std::vector<bool> check = verificaNulitatea(medicamente[0]);
	//verifica daca un membru al unui medicament este nul sau nu
	std::vector<std::vector<std::string>> deAfisat;
	std::vector<string> anteturi = { "ID", "Nume Stiintific", "Nume Comercial", "Producator", "Pret", "Data Fabricarii", "Data Expirarii", "Afectiunea Tratata", "FurnizorID" };
	std::vector<string> temp;
	for (int i = 0; i < anteturi.size(); i++) {
		if (check[i]) {
			temp.push_back(anteturi[i]);
		}
	}
	deAfisat.push_back(temp);
	for (int i = 0; i < medicamente.size(); i++) {
		std::vector<string> rand;
		rand.insert(rand.end(), { to_string(medicamente[i].getID()), medicamente[i].getNumeStiintific(), medicamente[i].getNumeComercial(), medicamente[i].getProducator(), to_string(medicamente[i].getPret()), medicamente[i].getDataFabricarii(), medicamente[i].getDataExpirarii(), medicamente[i].getAfectiuneTratata(), to_string(medicamente[i].getFurnizorID()) });
		deAfisat.push_back(rand);
	}

	for (auto& rand : deAfisat) {
		for (auto& col : rand) {
			rand.erase(remove_if(rand.begin(), rand.end(), eNulSauZero), rand.end());
		}
	}
	afisareMedicamente(deAfisat);
}

void FurnizoriToString(std::vector<Furnizor> furnizori) {
	std::vector<std::vector<std::string>> deAfisat;
	std::vector<string> anteturi = { "ID", "Nume", "Adresa", "Numar de Telefon"};
	std::vector<string> temp;
	for (int i = 0; i < anteturi.size(); i++) {
		temp.push_back(anteturi[i]);
	}
	deAfisat.push_back(temp);
	for (int i = 0; i < furnizori.size(); i++) {
		std::vector<string> rand;
		rand.insert(rand.end(), { to_string(furnizori[i].getID()), furnizori[i].getNume(), furnizori[i].getAdresa(), furnizori[i].getNumarDeTelefon() });
		deAfisat.push_back(rand);
	}

	for (auto& rand : deAfisat) {
		for (auto& col : rand) {
			rand.erase(remove_if(rand.begin(), rand.end(), eNulSauZero), rand.end());
		}
	}
	afisareFurnizori(deAfisat);
}

void afisareMedicamente(std::vector<std::vector<string>> deAfisat) {
	tabulate::Table table;
	for (int i = 0; i < deAfisat.size(); i++)
	{
		tabulate::Table::Row_t row(deAfisat[i].begin(), deAfisat[i].end());
		table.add_row(row);
	}

	for (auto& row : table) {
		row.format()
			.font_align(tabulate::FontAlign::left)
			.font_color(tabulate::Color::green);
	}
	for (int i = 0; i < table[0].size(); i++) {
		table[0].cell(i).format()
			.font_align(tabulate::FontAlign::left)
			.font_color(tabulate::Color::red);
	}
	for (int i = 0; i < deAfisat[0].size(); i++) {
		table.column(i).format().width(LATIME_MEDICAMENTE);
	}
	std::cout << table << std::endl;
}      

void afisareFurnizori(std::vector<std::vector<string>> deAfisat){
	tabulate::Table table;
	for (int i = 0; i < deAfisat.size(); i++)
	{
		tabulate::Table::Row_t row(deAfisat[i].begin(), deAfisat[i].end());
		table.add_row(row);
	}

	for (auto& row : table) {
		row.format()
			.font_align(tabulate::FontAlign::left)
			.font_color(tabulate::Color::green);
	}
	for (int i = 0; i < table[0].size(); i++) {
		table[0].cell(i).format()
			.font_align(tabulate::FontAlign::left)
			.font_color(tabulate:: Color::red);
	}
	for (int i = 0; i < deAfisat[0].size(); i++) {
		table.column(i).format().width(LATIME_FURNIZORI);
	}
	std::cout << table << std::endl;
}

void getMedicamente() {
	std::vector<Medicament> medicamente;
	string nume_comercial, producator, nume_stiintific, afectiune_tratata;
	int id, pret, furnizor_id;
	string data_fabricarii, data_expirarii;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* result = stmt->executeQuery("SELECT * FROM `medicamente`");
	int nrRanduri = result->rowsCount();
	for (int i = 1; i <= nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume_stiintific = result->getString("NumeStiintific");
			nume_comercial = result->getString("NumeComercial");
			producator = result->getString("Producator");
			pret = result->getInt("Pret");
			data_fabricarii = result->getString("DataFabricarii");
			data_expirarii = result->getString("DataExpirarii");
			afectiune_tratata = result->getString("AfectiuneTratata");
			furnizor_id = result->getInt("FurnizorID");
			Medicament medicament = Medicament(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, furnizor_id);
			medicamente.push_back(medicament);
		}
	}
	FiltrareAnteturiMedicamente(medicamente);

	delete stmt;
	delete result;
	delete con;
}

int getMedicamentDupaNumeSt(std::vector<Medicament> medicamente, string nume_stiintific) {
	for (int i = 0; i < medicamente.size(); i++) {
		if (medicamente[i].getNumeStiintific() == nume_stiintific)
			return i;
	}
	return medicamente.size() + 1;
}

int getMedicamentDupaNumeCom(std::vector<Medicament> medicamente, string nume_comercial) {
	for (int i = 0; i < medicamente.size(); i++) {
		if (medicamente[i].getNumeComercial() == nume_comercial)
			return i;
	}
	return medicamente.size() + 1;
}

int getFurnizorDupaNume(std::vector<Furnizor> furnizori, string nume) {
	for (int i = 0; i < furnizori.size(); i++) {
		if (furnizori[i].getNume() == nume)
			return i;
	}
	return furnizori.size() + 1;
}

int getFurnizorDupaID(std::vector<Furnizor> furnizori, int id) {
	for (int i = 0; i < furnizori.size(); i++) {
		if (furnizori[i].getID() == id)
			return i;
	}
	return furnizori.size() + 1;
}

void cautareDupaNumeComercial(std::vector<Medicament> medicamente) {
	medicamente.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");

	string nume_comercial = "", producator = "", nume_stiintific = "", afectiune_tratata = "";
	int id = 0, pret = 0, furnizor_id = 0;
	string data_fabricarii = "", data_expirarii = "";
	string nume_com_de_cautat="";
	cout << "Introduceti numele comercial al medicamentului cautat:\n";
	cin >> nume_com_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT `ID`, `NumeStiintific`, `NumeComercial`, `Producator`, `FurnizorID` FROM `medicamente` WHERE `NumeComercial` LIKE ?");
	nume_com_de_cautat = "%" + nume_com_de_cautat + "%";
	pstmt->setString(1, nume_com_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 1; i <= nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume_stiintific = result->getString("NumeStiintific");
			nume_comercial = result->getString("NumeComercial");
			producator = result->getString("Producator");
			furnizor_id = result->getInt("FurnizorID");
			Medicament medicament = Medicament(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, furnizor_id);
			medicamente.push_back(medicament);
		}
	}
	if (!medicamente.empty()) {
		FiltrareAnteturiMedicamente(medicamente);
	}
	else {
		cout << "Nu s-a gasit un medicament cu acel nume comercial.\n";
	}
	delete pstmt;
	delete result;
	delete con;
}

void cautareDupaNumeStiintific(std::vector<Medicament> medicamente) {
	medicamente.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");

	string nume_comercial="", producator="", nume_stiintific="", afectiune_tratata="";
	int id=0, pret=0, furnizor_id=0;
	string data_fabricarii="", data_expirarii="";
	string nume_stiintific_de_cautat="";
	cout << "Introduceti numele stiintific al medicamentului cautat:\n";
	cin >> nume_stiintific_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT `ID`, `NumeStiintific`, `NumeComercial`, `Producator`, `AfectiuneTratata`, `FurnizorID` FROM `medicamente` WHERE `NumeStiintific` LIKE ?");
	nume_stiintific_de_cautat = "%" + nume_stiintific_de_cautat + "%";
	pstmt->setString(1, nume_stiintific_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 1; i <= nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume_stiintific = result->getString("NumeStiintific");
			nume_comercial = result->getString("NumeComercial");
			producator = result->getString("Producator");
			afectiune_tratata = result->getString("AfectiuneTratata");
			furnizor_id = result->getInt("FurnizorID");
			Medicament medicament = Medicament(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, furnizor_id);
			medicamente.push_back(medicament);
		}
	}
	if (!medicamente.empty()) {
		FiltrareAnteturiMedicamente(medicamente);
	}
	else {
		cout << "Nu s-a gasit un medicament cu acel nume stiintific.\n";
	}
	delete pstmt;
	delete result;
	delete con;
}

void cautareDupaAfectiuneaTratata(std::vector<Medicament> medicamente) {
	medicamente.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");

	string nume_comercial = "", producator = "", nume_stiintific = "", afectiune_tratata = "";
	int id = 0, pret = 0, furnizor_id = 0;
	string data_fabricarii = "", data_expirarii = "";
	string afectiune_de_cautat="";
	cout << "Introduceti afectiunea pe care o trateaza medicamentul cautat:\n";
	cin >> afectiune_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT `ID`, `NumeStiintific`, `NumeComercial`, `Producator`, `AfectiuneTratata`, `FurnizorID` FROM `medicamente` WHERE `AfectiuneTratata` LIKE ?");
	afectiune_de_cautat = "%" + afectiune_de_cautat + "%";
	pstmt->setString(1, afectiune_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 1; i <= nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume_stiintific = result->getString("NumeStiintific");
			nume_comercial = result->getString("NumeComercial");
			producator = result->getString("Producator");
			afectiune_tratata = result->getString("AfectiuneTratata");
			furnizor_id = result->getInt("FurnizorID");
			Medicament medicament = Medicament(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, furnizor_id);
			medicamente.push_back(medicament);
		}
	}
	if (!medicamente.empty()) {
		//afisareMedicamente(medicamente);
		FiltrareAnteturiMedicamente(medicamente);
	}
	else {
		cout << "Nu s-a gasit un medicament ce trateaza acea afectiune.\n";
	}
	delete pstmt;
	delete result;
	delete con;
}

void cautareDupaProducator(std::vector<Medicament> medicamente) {
	medicamente.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");

	string nume_comercial = "", producator = "", nume_stiintific = "", afectiune_tratata = "";
	int id = 0, pret = 0, furnizor_id = 0;
	string data_fabricarii = "", data_expirarii = "";
	string producator_de_cautat="";
	cout << "Introduceti producatorul medicamentului cautat:\n";
	cin >> producator_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT `ID`, `NumeStiintific`, `NumeComercial`, `Producator`, `AfectiuneTratata`, `FurnizorID` FROM `medicamente` WHERE `Producator` LIKE ?");
	producator_de_cautat = "%" + producator_de_cautat + "%";
	pstmt->setString(1, producator_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 1; i <= nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume_stiintific = result->getString("NumeStiintific");
			nume_comercial = result->getString("NumeComercial");
			producator = result->getString("Producator");
			afectiune_tratata = result->getString("AfectiuneTratata");
			furnizor_id = result->getInt("FurnizorID");
			Medicament medicament = Medicament(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, furnizor_id);
			medicamente.push_back(medicament);
		}
	}
	if (!medicamente.empty()) {
		FiltrareAnteturiMedicamente(medicamente);
	}
	else {
		cout << "Nu s-a gasit un medicament produs de acea companie.\n";
	}
	delete pstmt;
	delete result;
	delete con;
}

void cautareDupaPret(std::vector<Medicament> medicamente) {
	medicamente.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");

	string nume_comercial = "", producator = "", nume_stiintific = "", afectiune_tratata = "";
	int id = 0, pret = 0, furnizor_id = 0;
	string data_fabricarii = "", data_expirarii = "";
	int pret_de_cautat=0;
	cout << "Introduceti pretul medicamentului cautat:\n";
	cin >> pret_de_cautat;
	sql:: PreparedStatement * pstmt = con->prepareStatement("SELECT `ID`, `NumeStiintific`, `NumeComercial`, `Producator`, `Pret`, `AfectiuneTratata`, `FurnizorID` FROM `medicamente` WHERE `Pret` LIKE ?");
	pstmt->setInt(1, pret_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 1; i <= nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume_stiintific = result->getString("NumeStiintific");
			nume_comercial = result->getString("NumeComercial");
			producator = result->getString("Producator");
			pret = result->getInt("Pret");
			afectiune_tratata = result->getString("AfectiuneTratata");
			furnizor_id = result->getInt("FurnizorID");
			Medicament medicament = Medicament(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, furnizor_id);
			medicamente.push_back(medicament);
		}
	}
	if (!medicamente.empty()) {
		FiltrareAnteturiMedicamente(medicamente);
	}
	else {
		cout << "Nu s-a gasit un medicament cu acel pret.\n";
	}
	delete pstmt;
	delete result;
	delete con;
}

void cautareDupaDataFabricarii(std::vector<Medicament> medicamente) {
	medicamente.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");

	string nume_comercial = "", producator = "", nume_stiintific = "", afectiune_tratata = "";
	int id = 0, pret = 0, furnizor_id = 0;
	string data_fabricarii = "", data_expirarii = "";
	string data_fabricarii_de_cautat = "";
	cout << "Introduceti data la care a fost fabricat medicamentul cautat:\n";
	cin >> data_fabricarii_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT `ID`, `NumeStiintific`, `NumeComercial`, `DataFabricarii`, `AfectiuneTratata`, `FurnizorID` FROM `medicamente` WHERE `DataFabricarii` LIKE ?");
	data_fabricarii_de_cautat = "%" + data_fabricarii_de_cautat + "%";
	pstmt->setString(1, data_fabricarii_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 1; i <= nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume_stiintific = result->getString("NumeStiintific");
			nume_comercial = result->getString("NumeComercial");
			data_fabricarii = result->getString("DataFabricarii");
			afectiune_tratata = result->getString("AfectiuneTratata");
			furnizor_id = result->getInt("FurnizorID");
			Medicament medicament = Medicament(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, furnizor_id);
			medicamente.push_back(medicament);
		}
	}
	if (!medicamente.empty()) {
		FiltrareAnteturiMedicamente(medicamente);
	}
	else {
		cout << "Nu s-a gasit un medicament produs de acea companie.\n";
	}
	delete pstmt;
	delete result;
	delete con;
}

void cautareDupaDataExpirarii(std::vector<Medicament> medicamente) {
	medicamente.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");

	string nume_comercial = "", producator = "", nume_stiintific = "", afectiune_tratata = "";
	int id = 0, pret = 0, furnizor_id = 0;
	string data_fabricarii = "", data_expirarii = "";
	string data_expirarii_de_cautat = "";
	cout << "Introduceti data la care a fost fabricat medicamentul cautat:\n";
	cin >> data_expirarii_de_cautat;
	sql:: PreparedStatement* pstmt = con->prepareStatement("SELECT `ID`, `NumeStiintific`, `NumeComercial`, `DataFabricarii`, `AfectiuneTratata`, `FurnizorID` FROM `medicamente` WHERE `DataExpirarii` LIKE ?");
	data_expirarii_de_cautat = "%" + data_expirarii_de_cautat + "%";
	pstmt->setString(1, data_expirarii_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 1; i <= nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume_stiintific = result->getString("NumeStiintific");
			nume_comercial = result->getString("NumeComercial");
			data_fabricarii = result->getString("DataFabricarii");
			afectiune_tratata = result->getString("AfectiuneTratata");
			furnizor_id = result->getInt("FurnizorID");
			Medicament medicament = Medicament(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, furnizor_id);
			medicamente.push_back(medicament);
		}
	}
	if (!medicamente.empty()) {
		FiltrareAnteturiMedicamente(medicamente);
	}
	else {
		cout << "Nu s-a gasit un medicament produs de acea companie.\n";
	}
	delete pstmt;
	delete result;
	delete con;
}

void stergeMedicament(std::vector<Medicament> medicamente) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	int id;
	cout << "Introduceti ID-ul medicamentului pe care doriti sa il stergeti:\n";
	cin >> id;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT `NumeComercial` FROM `medicamente` WHERE `ID` = ?");
	pstmt->setInt(1, id);
	sql::ResultSet* result = pstmt->executeQuery();
	if (result->rowsCount() == 0) {
		cout << "Nu exista un medicament cu acel ID.\n";
	}
	else {
		pstmt = con->prepareStatement("DELETE FROM `medicamente` WHERE `ID` = ?");
		pstmt->setInt(1, id);
		pstmt->execute();
		int pozitie_de_sters;
		for (int i = 0; i < medicamente.size(); i++) {
			if (medicamente[i].getID() == id)
				pozitie_de_sters = i;
		}
		medicamente.erase(medicamente.begin() + pozitie_de_sters);
		cout << "Acel medicament a fost sters.\n";
	}

	delete pstmt;
	delete result;
	delete con;
}
void ModificaNumeStMedicament(std::vector<Medicament> medicamente) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	string nume_stiintific_vechi, nume_stiintific_nou;
	cout << "Introduceti numele stiintific pe care doriti sa-l modificati:\n";
	cin >> nume_stiintific_vechi;
	cout << "Introduceti noul nume stiintific:\n";
	cin >> nume_stiintific_nou;
	sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE `medicamente` SET `NumeStiintific` = ? WHERE `NumeStiintific` = ?");
	pstmt->setString(1, nume_stiintific_nou);
	pstmt->setString(2, nume_stiintific_vechi);
	pstmt->execute();

	int pozitie_med_gasit = getMedicamentDupaNumeSt(medicamente, nume_stiintific_vechi);
	if (pozitie_med_gasit != medicamente.size() + 1) {
		medicamente[pozitie_med_gasit].setNumeStiintific(nume_stiintific_nou);
		cout << "Numele stiintific al acestui medicament a fost modificat cu succes!\n";
	}
	else {
		cout << "Nu a fost gasit un medicament cu acel nume stiintific!\n";
	}
	delete pstmt;
	delete con;
}

void ModificaNumeComMedicament(std::vector<Medicament> medicamente) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	string nume_comercial_vechi, nume_comercial_nou;
	cout << "Introduceti numele comercial pe care doriti sa-l modificati:\n";
	cin >> nume_comercial_vechi;
	cout << "Introduceti noul nume comercial:\n";
	cin >> nume_comercial_nou;
	sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE `medicamente` SET `NumeComercial` = ? WHERE `NumeComercial` = ?");
	pstmt->setString(1, nume_comercial_nou);
	pstmt->setString(2, nume_comercial_vechi);
	pstmt->execute();

	int pozitie_med_gasit = getMedicamentDupaNumeCom(medicamente, nume_comercial_vechi);
	if (pozitie_med_gasit != medicamente.size() + 1) {
		medicamente[pozitie_med_gasit].setNumeComercial(nume_comercial_nou);
		cout << "Numele comercial al acestui medicament a fost modificat cu succes!\n";
	}
	else {
		cout << "Nu a fost gasit un medicament cu acel nume comercial!\n";
	}
	delete pstmt;
	delete con;
}

void ModificaProducatorMedicament(std::vector<Medicament> medicamente) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	string producator_nou, nume_com_medicament;
	cout << "Introduceti numele comercial al medicamentului al carui producator doriti sa-l modificati:\n";
	cin >> nume_com_medicament;
	cout << "Introduceti noul producator:\n";
	cin >> producator_nou;
	sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE `medicamente` SET `Producator` = ? WHERE `NumeComercial` = ?");
	pstmt->setString(1, producator_nou);
	pstmt->setString(2, nume_com_medicament);
	pstmt->execute();

	int pozitie_med_gasit = getMedicamentDupaNumeCom(medicamente, nume_com_medicament);
	if (pozitie_med_gasit != medicamente.size() + 1) {
		medicamente[pozitie_med_gasit].setProducator(producator_nou);
		cout << "Producatorul acestui medicament a fost modificat cu succes!\n";
	}
	else {
		cout << "Nu s-a gasit un medicament cu acel nume comercial!\n";
	}
	delete pstmt;
	delete con;
}

void ModificaPretMedicament(std::vector<Medicament> medicamente) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	int pret_nou;
	string nume_com_medicament;
	cout << "Introduceti numele comercial al medicamentului al carui producator doriti sa-l modificati:\n";
	cin >> nume_com_medicament;
	cout << "Introduceti noul pret:\n";
	cin >> pret_nou;
	sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE `medicamente` SET `Pret` = ? WHERE `NumeComercial` = ?");
	pstmt->setInt(1, pret_nou);
	pstmt->setString(2, nume_com_medicament);
	pstmt->execute();

	int pozitie_med_gasit = getMedicamentDupaNumeCom(medicamente, nume_com_medicament);
	if (pozitie_med_gasit != medicamente.size() + 1) {
		medicamente[pozitie_med_gasit].setPret(pret_nou);
		cout << "Pret acestui medicament a fost modificat cu succes!\n";
	}
	else {
		cout << "Nu s-a gasit un medicament cu acel nume comercial!\n";
	}
	delete pstmt;
	delete con;
}

void ModificaAfectiuneTratataMedicament(std::vector<Medicament> medicamente) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	string afectiune_tratata_noua, nume_com_medicament;
	cout << "Introduceti numele comercial al medicamentului a carui afectiune tratata doriti sa o modificati:\n";
	cin >> nume_com_medicament;
	cout << "Introduceti noua afectiune tratata:\n";
	cin >> afectiune_tratata_noua;
	sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE `medicamente` SET `AfectiuneTratata` = ? WHERE `NumeComercial` = ?");
	pstmt->setString(1, afectiune_tratata_noua);
	pstmt->setString(2, nume_com_medicament);
	pstmt->execute();

	int pozitie_med_gasit = getMedicamentDupaNumeCom(medicamente, nume_com_medicament);
	if (pozitie_med_gasit != medicamente.size() + 1) {
		medicamente[pozitie_med_gasit].setAfectiuneTratata(afectiune_tratata_noua);
		cout << "Afectiunea pe care o trateaza acest medicament a fost modificata cu succes!\n";
	}
	else {
		cout << "Nu s-a gasit un medicament cu acel nume comercial!\n";
	}
	delete pstmt;
	delete con;
}

void ModificaFurnizorIDMedicament(std::vector<Medicament> medicamente) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	string nume_com_de_cautat;
	int furnizor_id;
	std::cout << "Introduceti medicamentul al carui furnizor doriti sa-l modificati:\n";
	std::cin >> nume_com_de_cautat;
	std::cout << "Introduceti noul furnizor id:\n";
	std::cin >> furnizor_id;
	sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE `medicamente` SET `FurnizorID` = ? WHERE `NumeComercial` = ?");
	pstmt->setInt(1, furnizor_id);
	pstmt->setString(2, nume_com_de_cautat);
	int pozitie_med_gasit = getMedicamentDupaNumeCom(medicamente, nume_com_de_cautat);
	if (pozitie_med_gasit != medicamente.size() + 1) {
		medicamente[pozitie_med_gasit].setFurnizorID(furnizor_id);
		cout << "Afectiunea pe care o trateaza acest medicament a fost modificata cu succes!\n";
	}
	else {
		cout << "Nu s-a gasit un medicament cu acel nume comercial!\n";
	}
	delete pstmt;
	delete con;
}

void addMedicament(std::vector<Medicament> medicamente) {
	string nume_comercial, producator, nume_stiintific, afectiune_tratata;
	int id, pret, furnizor_id;
	string data_fabricarii, data_expirarii, furnizor;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");

	cout << "Introduceti numele comercial al medicamentului: \n";
	cin >> nume_comercial;
	cout << "Introduceti numele stiintific al medicamentului: \n";
	cin >> nume_stiintific;
	cout << "Introduceti producatorul medicamentului: \n";
	cin >> producator;
	cout << "Introduceti pretul medicamentului: \n";
	cin >> pret;
	cout << "Introduceti data de fabricatie a medicamentului: \n";
	cin >> data_fabricarii;
	cout << "Introduceti data de expirare a medicamentului: \n";
	cin >> data_expirarii;
	cout << "Introduceti afectiunea pe care o trateaza medicamentul: \n";
	cin >> afectiune_tratata;
	cout << "Introduceti numele companiei ce furnizeaza medicamentul: \n";
	cin >> furnizor;
	sql::PreparedStatement* pstmt2 = con->prepareStatement("SELECT `ID` FROM `furnizori` WHERE `Nume` LIKE ?");
	furnizor = "%" + furnizor + "%";
	pstmt2->setString(1, furnizor);
	sql::ResultSet* result = pstmt2->executeQuery();
	while(result->next())
		furnizor_id = result->getInt("ID");
	sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO `medicamente`(`NumeStiintific`, `NumeComercial`, `Producator`, `Pret`, `DataFabricarii`, `DataExpirarii`, `AfectiuneTratata`, `FurnizorID`) VALUES (?,?,?,?,?,?,?,?)");
	pstmt->setString(1, nume_stiintific);
	pstmt->setString(2, nume_comercial);
	pstmt->setString(3, producator);
	pstmt->setInt(4, pret);
	pstmt->setDateTime(5, data_fabricarii);
	pstmt->setDateTime(6, data_expirarii);
	pstmt->setString(7, afectiune_tratata);
	pstmt->setInt(8, furnizor_id);
	pstmt->executeUpdate();
	sql::Statement* stmt = con->createStatement();
	result = stmt->executeQuery("SELECT `ID` FROM `medicamente` ORDER BY `ID` DESC LIMIT 1");
	while(result->next())
		id = result->getInt("ID");
	Medicament med(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, furnizor_id);
	cout << "Medicamentul a fost adaugat!\n";
	medicamente.push_back(med);
	delete result;
	delete pstmt;
	delete pstmt2;
	delete stmt;
	delete con;
}

void cautareDupaFurnizorMedicament(std::vector<Medicament> medicamente) {
	medicamente.clear();
	Furnizor furnizor;
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");

	string nume_comercial="", producator="", nume_stiintific="", afectiune_tratata="";
	int id=0, pret=0;
	string data_fabricarii="", data_expirarii="",adresa_furnizor="", numar_de_telefon_furnizor="";
	string nume_furnizor_de_cautat="";
	cout << "Introduceti furnizorul medicamentului cautat:\n";
	cin >> nume_furnizor_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT `medicamente`.`ID`, `medicamente`.`NumeStiintific`, `medicamente`.`NumeComercial`, `medicamente`.`Producator`, `medicamente`.`AfectiuneTratata`, `furnizori`.`Nume` FROM `medicamente` INNER JOIN `furnizori` ON `medicamente`.`FurnizorID` = `furnizori`.`ID` WHERE `furnizori`.`Nume` LIKE ?; ");
	string temp = nume_furnizor_de_cautat;
	nume_furnizor_de_cautat = "%" + nume_furnizor_de_cautat + "%";
	pstmt->setString(1, nume_furnizor_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();
	int nrRanduri = result->rowsCount();
	nume_furnizor_de_cautat = temp;
	for (int i = 1; i <= nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume_stiintific = result->getString("NumeStiintific");
			nume_comercial = result->getString("NumeComercial");
			producator = result->getString("Producator");
			afectiune_tratata = result->getString("AfectiuneTratata");
			Medicament medicament = Medicament(id, nume_comercial, nume_stiintific, producator, pret, data_fabricarii, data_expirarii, afectiune_tratata, 0);
			furnizor = Furnizor(0, nume_furnizor_de_cautat, adresa_furnizor, numar_de_telefon_furnizor);
			medicamente.push_back(medicament);
		}
	}
	if (!medicamente.empty()) {
		//copy paste FiltrareAnteturiMedicamente() si modifica 
		std::vector<bool> check = verificaNulitatea(medicamente[0]);
		check.push_back(1); //pentru numele furnizorului
		//verifica daca un membru al unui medicament este nul sau nu
		std::vector<std::vector<std::string>> deAfisat;
		std::vector<string> anteturi = { "ID", "Nume Stiintific", "Nume Comercial", "Producator", "Pret", "Data Fabricarii", "Data Expirarii", "Afectiunea Tratata", "FurnizorID", "Nume Furnizor"};
		std::vector<string> temp;
		for (int i = 0; i < anteturi.size(); i++) {
			if (check[i]) {
				temp.push_back(anteturi[i]);
			}
		}
		deAfisat.push_back(temp);
		for (int i = 0; i < medicamente.size(); i++) {
			std::vector<string> rand;
			rand.insert(rand.end(), { to_string(medicamente[i].getID()), medicamente[i].getNumeStiintific(), medicamente[i].getNumeComercial(), medicamente[i].getProducator(), to_string(medicamente[i].getPret()), medicamente[i].getDataFabricarii(), medicamente[i].getDataExpirarii(), medicamente[i].getAfectiuneTratata(), to_string(medicamente[i].getFurnizorID()), furnizor.getNume()});
			deAfisat.push_back(rand);
		}

		for (auto& rand : deAfisat) {
			for (auto& col : rand) {
				rand.erase(remove_if(rand.begin(), rand.end(), eNulSauZero), rand.end());
			}
		}
		afisareMedicamente(deAfisat);
	}
	else {
		cout << "Nu s-a gasit un medicament furnizat de acea companie.\n";
	}
	delete pstmt;
	delete result;
	delete con;
}

void getAnteturiFurnizor(std::vector<Furnizor> furnizori) {
	std::vector<std::vector<string>> deAfisat;
	for (int i = 0; i < furnizori.size(); i++) {
		std::vector<string> rand;
		rand.insert(rand.end(), {to_string(furnizori[i].getID()), furnizori[i].getNume(), furnizori[i].getAdresa(), furnizori[i].getNumarDeTelefon()});
		deAfisat.push_back(rand);
	}
	deAfisat.insert(deAfisat.begin(), { "ID", "Nume", "Adresa", "Numar de Telefon" });
	afisareFurnizori(deAfisat);
}

void getFurnizori()
{
	std::vector<Furnizor> furnizori;
	int id;
	string nume, adresa, numar_de_telefon;
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("farmacie");
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* result = stmt->executeQuery("SELECT * FROM `furnizori`");
	int nrRanduri = result->rowsCount();
	for (int i = 0; i < nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume = result->getString("Nume");
			adresa = result->getString("Adresa");
			numar_de_telefon = result->getString("NumarDeTelefon");
			Furnizor furnizor(id, nume, adresa, numar_de_telefon);
			furnizori.push_back(furnizor);
		}
	}
	getAnteturiFurnizor(furnizori);
	delete stmt;
	delete result;
	delete con;
}

void addFurnizor(std::vector<Furnizor> furnizori) {
	int id;
	std::string numar_de_telefon, nume, adresa;
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");

	std::cout << "Introduceti numele furnizorului:\n";
	std:: cin >> nume;
	std::cout << "Introduceti adresa furnizorului:\n";
	std::cin >> adresa;
	std::cout << "Introduceti numarul de telefon al furnizorului:\n";
	std::cin >> numar_de_telefon;
	sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO `furnizori`(`Nume`, `Adresa`, `NumarDeTelefon`) VALUES (?,?,?,?)");
	pstmt->setString(1, nume);
	pstmt->setString(2, adresa);
	pstmt->setString(3, numar_de_telefon);

	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* result = stmt->executeQuery("SELECT `ID` FROM `furnizori` ORDER BY `ID` DESC LIMIT 1");
	id = result->getInt("ID");
	Furnizor furnizor(id, nume, adresa, numar_de_telefon);
	std::cout << "Furnizorul a fost adaugat cu succes!\n";
	furnizori.push_back(furnizor);
	delete pstmt;
	delete stmt;
	delete result;
	delete con;
}

void cautareDupaNumeFurnizor(std::vector<Furnizor> furnizori) {
	furnizori.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");

	int id=0;
	std::string nume="", adresa="", numar_de_telefon="", nume_de_cautat="";
	std::cout << "Introduceti numele furnizorului de cautat:\n";
	std::cin >> nume_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM `furnizori` WHERE `Nume` LIKE ?");
	nume_de_cautat = "%" + nume_de_cautat + "%";
	pstmt->setString(1, nume_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 0; i < nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume = result->getString("Nume");
			adresa = result->getString("Adresa");
			numar_de_telefon = result->getString("NumarDeTelefon");
			Furnizor furnizor(id, nume, adresa, numar_de_telefon);
			furnizori.push_back(furnizor);
		}
	}
	if (!furnizori.empty()) {
		FurnizoriToString(furnizori);
	}
	else {
		std::cout << "Nu exista un furnizor cu acel nume!\n";
	}
	delete result;
	delete pstmt;
	delete con;
}

void cautareDupaIDFurnizor(std::vector<Furnizor> furnizori) {
	furnizori.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");

	int id = 0, id_de_cautat=0;
	std::string nume = "", adresa = "", numar_de_telefon = "";
	std::cout << "Introduceti numele furnizorului de cautat:\n";
	std::cin >> id_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM `furnizori` WHERE `ID` = ?");
	pstmt->setInt(1, id_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 0; i < nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume = result->getString("Nume");
			adresa = result->getString("Adresa");
			numar_de_telefon = result->getString("NumarDeTelefon");
			Furnizor furnizor(id, nume, adresa, numar_de_telefon);
			furnizori.push_back(furnizor);
		}
	}
	if (!furnizori.empty()) {
		FurnizoriToString(furnizori);
	}
	else {
		std::cout << "Nu exista un furnizor cu acel id!\n";
	}
	delete result;
	delete pstmt;
	delete con;
}

void cautareDupaAdresaFurnizor(std::vector<Furnizor> furnizori) {
	furnizori.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");

	int id = 0;
	std::string nume = "", adresa = "", numar_de_telefon = "", adresa_de_cautat = "";
	std::cout << "Introduceti adresa furnizorului de cautat:\n";
	std::cin >> adresa_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM `furnizori` WHERE `Adresa` LIKE ?");
	adresa_de_cautat = "%" + adresa_de_cautat + "%";
	pstmt->setString(1, adresa_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 0; i < nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume = result->getString("Nume");
			adresa = result->getString("Adresa");
			numar_de_telefon = result->getString("NumarDeTelefon");
			Furnizor furnizor(id, nume, adresa, numar_de_telefon);
			furnizori.push_back(furnizor);
		}
	}
	if (!furnizori.empty()) {
		FurnizoriToString(furnizori);
	}
	else {
		std::cout << "Nu exista un furnizor cu acea adresa!\n";
	}
	delete result;
	delete pstmt;
	delete con;
}

void cautareDupaNumarDeTelefonFurnizor(std::vector<Furnizor> furnizori) {
	furnizori.clear();
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");

	int id = 0;
	std::string nume = "", adresa = "", numar_de_telefon = "", numar_de_telefon_de_cautat = "";
	std::cout << "Introduceti numarul de telefon al furnizorului de cautat:\n";
	std::cin >> numar_de_telefon_de_cautat;
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM `furnizori` WHERE `NumarDeTelefon` LIKE ?");
	numar_de_telefon_de_cautat = "%" + numar_de_telefon_de_cautat + "%";
	pstmt->setString(1, numar_de_telefon_de_cautat);
	sql::ResultSet* result = pstmt->executeQuery();

	int nrRanduri = result->rowsCount();
	for (int i = 0; i < nrRanduri; i++) {
		while (result->next()) {
			id = result->getInt("ID");
			nume = result->getString("Nume");
			adresa = result->getString("Adresa");
			numar_de_telefon = result->getString("NumarDeTelefon");
			Furnizor furnizor(id, nume, adresa, numar_de_telefon);
			furnizori.push_back(furnizor);
		}
	}
	if (!furnizori.empty()) {
		FurnizoriToString(furnizori);
	}
	else {
		std::cout << "Nu exista un furnizor cu acel numar de telefon!\n";
	}
	delete result;
	delete pstmt;
	delete con;
}

void ModificaNumeFurnizor(std::vector<Furnizor> furnizori) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	string nume_vechi, nume_nou;
	cout << "Introduceti numele pe care doriti sa-l modificati:\n";
	cin >> nume_vechi;
	cout << "Introduceti noul nume:\n";
	cin >> nume_nou;
	sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE `furnizori` SET `Nume` = ? WHERE `Nume` = ?");
	pstmt->setString(1, nume_nou);
	pstmt->setString(2, nume_vechi);

	int pozitie_furnizor_gasit = getFurnizorDupaNume(furnizori, nume_vechi);
	if (pozitie_furnizor_gasit != furnizori.size() + 1) {
		furnizori[pozitie_furnizor_gasit].settNume(nume_nou);
		std::cout << "Numele furnizorului a fost modificat cu succes!\n";
	}
	else {
		std::cout << "Nu a fost gasit un furnizor cu acel nume!\n";
	}
	delete pstmt;
	delete con;
}

void ModificaAdresaFurnizor(std::vector<Furnizor> furnizori) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	string nume, adresa;
	cout << "Introduceti numele furnizorului a carui adresa doriti sa o modificati:\n";
	cin >> nume;
	cout << "Introduceti noua adresa:\n";
	cin >> adresa;
	sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE `furnizori` SET `Adresa` = ? WHERE `Nume` = ?");
	pstmt->setString(1, adresa);
	pstmt->setString(2, nume);

	int pozitie_furnizor_gasit = getFurnizorDupaNume(furnizori, nume);
	if (pozitie_furnizor_gasit != furnizori.size() + 1) {
		furnizori[pozitie_furnizor_gasit].setAdresa(adresa);
		std::cout << "Adresa furnizorului a fost modificata cu succes!\n";
	}
	else {
		std::cout << "Nu a fost gasit un furnizor ce se afla la acea adresa!\n";
	}
	delete pstmt;
	delete con;
}

void ModificaNumarDeTelefonFurnizor(std::vector<Furnizor> furnizori) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	string nume, numar_de_telefon;
	cout << "Introduceti numele furnizorului al carui numar de telefon doriti sa-l modificati:\n";
	cin >> nume;
	cout << "Introduceti noul numar de telefon:\n";
	cin >> numar_de_telefon;
	sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE `furnizori` SET `NumarDeTelefon` = ? WHERE `Nume` = ?");
	pstmt->setString(1, numar_de_telefon);
	pstmt->setString(2, nume);

	int pozitie_furnizor_gasit = getFurnizorDupaNume(furnizori, nume);
	if (pozitie_furnizor_gasit != furnizori.size() + 1) {
		furnizori[pozitie_furnizor_gasit].setNumarDeTelefon(numar_de_telefon);
		std::cout << "Numarul de telefon al furnizorului a fost modificat cu succes!\n";
	}
	else {
		std::cout << "Nu a fost gasit un furnizor care are acel numar de telefon!\n";
	}
	delete pstmt;
	delete con;
}

void stergeFurnizor(std::vector<Furnizor> furnizori) {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("farmacie");
	int id, nou_furnizor_id=0;
	std::cout << "Introduceti ID-ul furnizorului pe care doriti sa-l stergeti:\n";
	std::cin >> id;
	std::cout << "Introduceti un furnizor id pentru medicamentele care aveau acel furnizor id:\n";
	std::cin >> nou_furnizor_id;
	int pozitie_furnizor_de_sters = getFurnizorDupaID(furnizori, id);
	sql::PreparedStatement* pstmt = con->prepareStatement("SELECT `Nume` FROM `furnizori` WHERE `ID` = ?");
	pstmt->setInt(1, id);
	sql::ResultSet* result = pstmt->executeQuery();
	if (result->rowsCount() == 0) {
		std::cout << "Nu exista un furnizor cu acel ID.\n";
	}
	else {
		pstmt = con->prepareStatement("DELETE FROM `furnizori` WHERE `ID` = ?");
		pstmt->setInt(1, id);
		pstmt->execute();
		furnizori.erase(furnizori.begin() + pozitie_furnizor_de_sters);
		pstmt = con->prepareStatement("UPDATE `medicamente` SET `FurnizorID` = ?");
		pstmt->setInt(1, nou_furnizor_id);
		std::cout << "Acel funizor a fost sters si medicamentele furnizate de acesta au un nou furnizor.\n";
	}
	delete pstmt;
	delete result;
	delete con;
}