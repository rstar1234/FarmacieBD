#include <iostream>
#include "Connection.h"
using namespace std;

string server = "tcp://127.0.0.1:3306";
string username = "root";
string password = "root";
sql::Driver* driver;
sql::Connection* con;