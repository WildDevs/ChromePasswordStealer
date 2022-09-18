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
#include "mainwindowcontroller.h"
#include <QStringListModel>
#include <QMenu>
#include <QDebug>
#include <QStandardItemModel>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;

void MainWindowController::setView(MainWindow* view)
{
    this->view = view;
}

MainWindow* MainWindowController::getView()
{
    return this->view;
}

void MainWindowController::setModel(MainWindowModel* model)
{
    this->model = model;
}

MainWindowModel* MainWindowController::getModel()
{
    return this->model;
}

MainWindowController::MainWindowController(MainWindow* view, MainWindowModel* model)
{
    this->setView(view);
    this->setModel(model);

    connect(this->getView()->btnGetDatabase, SIGNAL(clicked()), this->getModel(), SLOT(copyDatabase()));
    connect(this->getModel(), SIGNAL(gotDatabase()), this, SLOT(updateAvailableDatabases()));

    this->getView()->lvAvailableDatabases->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this->getView()->lvAvailableDatabases, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ContextMenuForAvailableDatabases(const QPoint &)));

    this->getView()->show();

    this->updateAvailableDatabases();
}

template<typename Out>
void split(const string &s, char delim, Out result)
{
    stringstream ss;
    ss.str(s);
    string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim)
{
    vector<string> tokens;
    split(s, delim, back_inserter(tokens));
    return tokens;
}

void MainWindowController::updateDatabaseContent(const char* dbFile){

    QStandardItemModel* listmodel = static_cast<QStandardItemModel *>(this->getView()->tvDatabaseContent->model());

    vector<string>* dbcontent = this->getModel()->getDataBaseContent(dbFile);
    for(int i = 0; i < dbcontent->size(); i++)
    {
        vector<string> tokens = split(dbcontent->at(i), ',');
        for(int k = 0; k < tokens.size(); k++)
        {
            QStandardItem *insert = new QStandardItem(QString(tokens.at(k).c_str()));
            listmodel->setItem(i, k, insert);
        }
    }

    this->getView()->tvDatabaseContent->setModel(listmodel);

    delete dbcontent;
}

void MainWindowController::updateAvailableDatabases()
{
    this->getView()->lvAvailableDatabases->clear();

    vector<string>* databaselist = this->getModel()->getFileHandler()->getDirContent("Databases");

    for(int i = 0; i < databaselist->size(); i++)
    {
        this->getView()->lvAvailableDatabases->addItem(QString::fromStdString(databaselist->at(i)));
    }

    delete databaselist;
}

void MainWindowController::ContextMenuForAvailableDatabases(const QPoint &pos)
{
    QPoint item = this->getView()->lvAvailableDatabases->mapToGlobal(pos);
    QMenu submenu;
    submenu.addAction("Delete");
    submenu.addAction("Show Content");
    QAction* rightClickItem = submenu.exec(item);
    if (rightClickItem)
    {
        QListWidgetItem* selectedItem = this->getView()->lvAvailableDatabases->currentItem();
        string filePath = "Databases\\";
        filePath.append(selectedItem->text().toStdString().c_str());

        if(rightClickItem->text().contains("Delete"))
        {
            this->getModel()->getFileHandler()->deleteFile(LPCSTR(filePath.c_str()));
            delete selectedItem;
        }
        if (rightClickItem->text().contains("Show Content"))
        {
            this->updateDatabaseContent(filePath.c_str());
        }
    }
}

MainWindowController::~MainWindowController()
{
    delete this->getView();
    delete this->getModel();
}
