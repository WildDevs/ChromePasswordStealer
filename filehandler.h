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
#ifndef FILEHANDLER_H
#define FILEHANDLER_H
using namespace std;

#include <QObject>
#include <Windows.h>

class FileHandler: public QObject
{
    Q_OBJECT

public:
    FileHandler();
    bool createDir(LPCSTR dir);
    bool deleteDir(LPCSTR dir);
    bool deleteFile(LPCSTR file);
    bool copyFile(LPCSTR src, LPCSTR dest);
    vector<string>* getDirContent(LPCSTR dir);
};

#endif // FILEHANDLER_H
