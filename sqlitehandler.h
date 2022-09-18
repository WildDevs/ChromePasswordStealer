/* Copyright (C) 2017 Eray Sönmez, www.ray-works.de
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your option)
 * any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SQLITEHANDLER_H
#define SQLITEHANDLER_H
#include "sqlite3.h"
#include <vector>
#include <QDebug>
#include <Windows.h>
#include <Wincrypt.h>
#pragma comment(lib, "crypt32.lib")
using namespace std;

class SQLiteHandler
{
private:
    sqlite3* db;
public:
    SQLiteHandler();
    sqlite3* getDB();
    void connectToDatabase(const char* dbFile);
    void disconnectFromCurrentDatabase();
    vector<string>* getPasswords();
};

#endif // SQLITEHANDLER_H
