#pragma once
#include <iostream>
#include <vector>

class Medicament
{
	int MedicamentID;
	std::string MedicamentNumeComercial;
	std::string MedicamentNumeStiintific;
	std::string MedicamentProducator;
	int MedicamentPret;
	std::string MedicamentDataFabricarii;
	std::string MedicamentDataExpirarii;
	std::string MedicamentAfectiuneTratata;
	int FurnizorID;
public:
	static std::vector<std::vector<std::string>> deAfisat;

	//update the constructor with FurnizorID later

public:
	Medicament(int id, std::string nume_comercial, std::string nume_stiintific, std::string producator, int pret, std::string data_fabricarii, std::string data_expirarii, std::string afectiune_tratata, int furnizor_id);
	Medicament();
	
	int getID();
	std::string getNumeComercial();
	std::string getNumeStiintific();
	std::string getProducator();
	int getPret();
	std::string getDataFabricarii();
	std::string getDataExpirarii();
	std::string getAfectiuneTratata();
	int getFurnizorID();
	void InitializareVector(std::vector<Medicament> medicamente);
	void setNumeComercial(std::string nume);
	void setNumeStiintific(std::string firma);
	void setProducator(std::string producator);
	void setPret(int pret);
	void setAfectiuneTratata(std::string afectiune_tratata);
	void setFurnizorID(int furnizor_id);
};

