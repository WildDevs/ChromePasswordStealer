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
#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>
#include "filehandler.h"
#include "sqlitehandler.h"

class MainWindowModel : public QObject
{
    Q_OBJECT

private:
    FileHandler* fileHandler;
    SQLiteHandler* sqliteHandler;
    void setFileHandler(FileHandler* fileHandler);
    void setSqliteHandler(SQLiteHandler* sqliteHandler);
public:
    FileHandler* getFileHandler();
    SQLiteHandler* getSqliteHandler();
    vector<string>* getDataBaseContent(const char* dbFile);
    MainWindowModel();
    ~MainWindowModel();

signals:
    void gotDatabase();

public slots:
    void copyDatabase();
};

#endif // MAINWINDOWMODEL_H
