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
#include "mainwindowcontroller.h"
#include "mainwindowmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow* view = new MainWindow();
    MainWindowModel* model = new MainWindowModel();
    new MainWindowController(view, model);

    return a.exec();
}
