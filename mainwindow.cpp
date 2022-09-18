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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->btnGetDatabase = this->ui->btnGetDatabase;
    this->lvAvailableDatabases = this->ui->lvAvailableDatabases;
    this->tvDatabaseContent = this->ui->tvDatabaseContent;
    this->setFixedSize(QSize(1100,600));

    QStandardItemModel* listmodel = new QStandardItemModel(0,3,this->tvDatabaseContent);
    listmodel->setHorizontalHeaderItem(0, new QStandardItem(QString("Web URL")));
    listmodel->setHorizontalHeaderItem(1, new QStandardItem(QString("Username")));
    listmodel->setHorizontalHeaderItem(2, new QStandardItem(QString("Password")));
    this->tvDatabaseContent->setModel(listmodel);

    this->tvDatabaseContent->setColumnWidth(0, 470);
    this->tvDatabaseContent->setColumnWidth(1, this->tvDatabaseContent->width()/4);
    this->tvDatabaseContent->setColumnWidth(2, this->tvDatabaseContent->width()/4);
}

MainWindow::~MainWindow()
{
    delete ui;
}
