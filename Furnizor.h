#pragma once
#include <iostream>
#include <vector>

class Furnizor
{
	int FurnizorID;
	std::string FurnizorNume;
	std::string FurnizorAdresa;
	std::string FurnizorNumarDeTelefon;
public:
	Furnizor(int id, std::string nume, std::string adresa, std::string numar_de_telefon);
	Furnizor();
	~Furnizor();
	int getID();
	std::string getNume();
	std::string getAdresa();
	std::string getNumarDeTelefon();
	void setID(int  id);
	void settNume(std::string nume);
	void setAdresa(std::string adresa);
	void setNumarDeTelefon(std::string numar_de_telefon);
};

