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
#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include "mainwindow.h"
#include "mainwindowmodel.h"
#pragma comment(lib, "user32.lib")

class MainWindowController : public QObject
{
    Q_OBJECT

private:
    MainWindow* view;
    MainWindowModel* model;

public:
    void setView(MainWindow* view);
    void setModel(MainWindowModel* model);
    MainWindow* getView();
    MainWindowModel* getModel();
    void updateDatabaseContent(const char* dbFile);

    MainWindowController(MainWindow* view, MainWindowModel* model);
    ~MainWindowController();

public slots:
    void ContextMenuForAvailableDatabases(const QPoint &pos);
    void updateAvailableDatabases();
};

#endif // MAINWINDOWCONTROLLER_H
