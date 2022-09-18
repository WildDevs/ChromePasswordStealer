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
#include "mainwindowmodel.h"
#include <fstream>
#include <QDebug>
#include <time.h>
using namespace std;

void MainWindowModel::setFileHandler(FileHandler* fileHandler)
{
    this->fileHandler = fileHandler;
}

FileHandler* MainWindowModel::getFileHandler()
{
    return this->fileHandler;
}

void MainWindowModel::setSqliteHandler(SQLiteHandler* sqliteHandler)
{
    this->sqliteHandler = sqliteHandler;
}

SQLiteHandler* MainWindowModel::getSqliteHandler()
{
    return this->sqliteHandler;
}

MainWindowModel::MainWindowModel()
{
    this->setFileHandler(new FileHandler());
    this->setSqliteHandler(new SQLiteHandler());
}

void MainWindowModel::copyDatabase()
{
    string databaseDir = "Databases";

    this->getFileHandler()->createDir(LPCSTR(databaseDir.c_str()));
    string chromeDatabasePath = getenv("LOCALAPPDATA");
    chromeDatabasePath.append("\\Google\\Chrome\\User Data\\Default\\Login Data");

    time_t now = time(0);
    tm *ltm = localtime(&now);


    string fileCopyName = databaseDir.append("\\")
                                    .append("chromePasswordDatabase-")
                                    .append(to_string(1900 + ltm->tm_year) + "-")
                                    .append(to_string(1 + ltm->tm_mon) + "-")
                                    .append(to_string(ltm->tm_mday) + "-")
                                    .append((((ltm->tm_hour) < 10) ? "0" + to_string(ltm->tm_hour) : to_string(ltm->tm_hour)) + "-")
                                    .append((((ltm->tm_min) < 10) ? "0" + to_string(ltm->tm_min) : to_string(ltm->tm_min)) + "-")
                                    .append((((ltm->tm_sec) < 10) ? "0" + to_string(ltm->tm_sec) : to_string(ltm->tm_sec)));

    LPCSTR src = LPCSTR(chromeDatabasePath.c_str());
    LPCSTR dest = LPCSTR(fileCopyName.c_str());

    if(this->getFileHandler()->copyFile(src, dest)){
        emit gotDatabase();
    } else {
        qInfo() << "File Not Found";
    }
}

vector<string>* MainWindowModel::getDataBaseContent(const char* dbFile){
    this->getSqliteHandler()->connectToDatabase(dbFile);
    vector<string>* dbcontent = this->getSqliteHandler()->getPasswords();
    this->getSqliteHandler()->disconnectFromCurrentDatabase();
    return dbcontent;
}

MainWindowModel::~MainWindowModel()
{
  delete this->getFileHandler();
}
