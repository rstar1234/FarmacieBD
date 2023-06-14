#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Furnizor.h"
#include "Connection.h"

Furnizor::Furnizor(int id, string nume, string adresa, string numar_de_telefon) {
    FurnizorID = id;
    FurnizorNume = nume;
    FurnizorAdresa = adresa;
    FurnizorNumarDeTelefon = numar_de_telefon;
}

Furnizor::Furnizor()
{
}

Furnizor::~Furnizor()
{
}

int Furnizor::getID()
{
    return FurnizorID;
}

string Furnizor::getNume()
{
    return FurnizorNume;
}

string Furnizor::getAdresa()
{
    return FurnizorAdresa;
}

string Furnizor::getNumarDeTelefon()
{
    return FurnizorNumarDeTelefon;
}

void Furnizor::setID(int id)
{
    FurnizorID = id;
}

void Furnizor::settNume(string nume)
{
    FurnizorNume = nume;
}

void Furnizor::setAdresa(string adresa)
{
    FurnizorAdresa = adresa;
}

void Furnizor::setNumarDeTelefon(string numar_de_telefon)
{
    FurnizorNumarDeTelefon = numar_de_telefon;
}
