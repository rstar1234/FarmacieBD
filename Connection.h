#pragma once
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

extern string server;
extern string username;
extern string password;
extern sql::Driver* driver;
extern sql::Connection* con;